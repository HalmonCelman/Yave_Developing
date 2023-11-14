/*
YAVE - by MAKOUS and KK
*/

#include <stdint.h>
#include <ctime>

#include "API/yave.h"

int main()
{
    Yave_Init();    //init engine

    Sound_CreateListener(); //init music
    UpdateListener();
    
    Object obj1,obj2;
    obj1.isAnimated=true;
    obj1.ModelFile="animations/Ymca_Dance/Ymca_Dance.dae";
    obj1.AnimationFile="animations/Ymca_Dance/Ymca_Dance.dae";
    obj1.SoundFile="music/YMCA.wav";
    obj1.position={-2.0f,0.0f,-11.0f};
    obj1.Init();



    obj2.isAnimated=true;
    obj2.ModelFile="animations/Flair/Flair.dae";
    obj2.AnimationFile="animations/Flair/Flair.dae";
    obj2.noSound = true;
    obj2.Init();

    Object terrain[12][12];

    srand(time(0));         //just to get random colors

    for(uint8_t i=0;i<12;i++){
        for(uint8_t j=0;j<12;j++){
            terrain[i][j].color[0]=(rand()%1000)/1000.0f;
            terrain[i][j].color[1]=(rand()%1000)/1000.0f;
            terrain[i][j].color[2]=(rand()%1000)/1000.0f;
            terrain[i][j].noSound=true;
            terrain[i][j].ModelFile="models/cube.glb";
            terrain[i][j].position={11-(float)2*i,-1.0f,-(float)2*j};
            terrain[i][j].Init();
        }
    }

    obj1.PlaySound(); // ! remember to put PlaySound() just before render loop - not earlier
    cam.Position[1]=1.0f;
    while (YAVE_activeWindow())
    {
        YAVE_executeEvents();
        YAVE_prepareRender();

        UpdateListener();

        obj1.Render();
        obj2.Render();

        for(uint8_t i=0;i<12;i++){
            for(uint8_t j=0;j<12;j++){
                terrain[i][j].Render();
            }
        }
    }

    

    Sound_DeleteListener();
    Yave_End();
	return 0;
}



