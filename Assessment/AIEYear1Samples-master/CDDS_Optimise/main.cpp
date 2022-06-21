#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "ResourceManager.h"
#include "ObjectPool.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //TODO:Optimise collisions
    //Optimise loading textures alot. use hash table to load the texture. look at set/map
    //


    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));

    //ResourceManager textureManager;
    const char critterTexture[] = "res/10.png";
    const char destroyerTexture[] = "res/9.png";
    const int CRITTER_COUNT = 50;
    ObjectPool critterpool(CRITTER_COUNT);

    const int MAX_VELOCITY = 80;

    for (int i = 0; i < CRITTER_COUNT - 1; i++)
    {
        *critterpool.GetPool(i) = *critterpool.spawn();
    }

    for (Critter critters : critterpool.GetActive()) {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
        critters.Init(
            { (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
            velocity,
            12, critterTexture);
    }

    Critter* destroyer = critterpool.spawn();
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }
    ,velocity, 20, destroyerTexture);


    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        float delta = GetFrameTime();

        // update the critters
        for (Critter critters : critterpool.GetActive())
        {
            critters.Update(delta);

            // check each critter against screen bounds
            if (critters.GetX() < 0) {
                critters.SetX(0);
                critters.SetVelocity(Vector2{ -critters.GetVelocity().x, critters.GetVelocity().y });
            }
            if (critters.GetX() > screenWidth) {
                critters.SetX(screenWidth);
                critters.SetVelocity(Vector2{ -critters.GetVelocity().x, critters.GetVelocity().y });
            }
            if (critters.GetY() < 0) {
                critters.SetY(0);
                critters.SetVelocity(Vector2{ critters.GetVelocity().x, -critters.GetVelocity().y });
            }
            if (critters.GetY() > screenHeight) {
                critters.SetY(screenHeight);
                critters.SetVelocity(Vector2{ critters.GetVelocity().x, -critters.GetVelocity().y });
            }


            float dist = Vector2Distance(critters.GetPosition(), destroyer.GetPosition());
            if (dist < critters.GetRadius() + destroyer.GetRadius())
            {
                critterpool.despawn(critters);
            }
        }

        for(int i = 0; i < critterpool.GetActive().size(); i++){
            for (int j = 0; j < critterpool.GetActive().size(); j++) {
                if (critterpool.GetPool(i) == critterpool.GetPool(j) || critterpool.GetPool(i)->IsDirty()) // note: the other critter (j) could be dirty - that's OK
                    continue;

                // check every critter against every other critter
                float dist = Vector2Distance(critterpool.GetPool(i)->GetPosition(), critterpool.GetPool(j)->GetPosition());
                if (dist < critterpool.GetPool(i)->GetRadius() + critterpool.GetPool(j)->GetRadius())
                {
                    // collision!
                    // do math to get critters bouncing
                    Vector2 normal = Vector2Normalize(Vector2Subtract(critterpool.GetPool(j)->GetPosition(), critterpool.GetPool(i)->GetPosition()));

                    // not even close to real physics, but fine for our needs
                    critterpool.GetPool(i)->SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                    // set the critter to *dirty* so we know not to process any more collisions on it
                    critterpool.GetPool(i)->SetDirty();

                    // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                    // to make sure the other critter is clean before we do the collision response
                    if (!critterpool.GetPool(j)->IsDirty()) {
                        critterpool.GetPool(j)->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        critterpool.GetPool(j)->SetDirty();
                    }
                    break;
                }
            }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            // find any dead critters and spit them out (respawn)
            for (Critter critters : critterpool.GetInactive()) {
                Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

                // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                Vector2 pos = destroyer.GetPosition();
                pos = Vector2Add(pos, Vector2Scale(normal, -50));
                // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
                critterpool.spawn();
                //critters.Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");
                break;
            }
        }
        nextSpawnPos = destroyer.GetPosition();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        for (Critter critters : critterpool.GetActive()){
            critters.Draw();
        }
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!)
        destroyer.Draw();

        DrawFPS(10, 10);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (Critter critters : critterpool.GetActive())
    {
        critters.Destroy();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}