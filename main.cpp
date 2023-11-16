/*
YAVE - by MAKOUS and KK
*/

#include <stdint.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>

#include "API/yave.h"

// configuration of example
const int numberOfMeeples=10;
const int XTerrain = 12;
const int ZTerrain = 12;
const float distanceOfMeeples=10;

// some configuration for rotate meeples function
int totalCount=0;
auto lastt=std::chrono::high_resolution_clock::now();
const int dt=10;
const double Period=10000;

Object meeple[numberOfMeeples];
Object terrain[XTerrain][ZTerrain];

void RenderLoop(void);      //main loop
void RotateMeeples(void);   //thread 1

int main()
{
    // initializations
    Yave_Init();    //init engine

    Sound_CreateListener(); //init music
    cam.Position={0,1.0f,0};
    UpdateListener();

    float meepleAngle;
    for(int i=0;i<numberOfMeeples;i++){
        if(i)
            meepleAngle=2*3.14/numberOfMeeples*i;
        else
            meepleAngle=0;
        meeple[i].isAnimated=true;
        meeple[i].noSound=true;
        meeple[i].ModelFile="animations/Flair/Flair.dae";
        meeple[i].AnimationFile="animations/Flair/Flair.dae";
        meeple[i].position={(float)(distanceOfMeeples*sin(meepleAngle)),0,(float)(distanceOfMeeples*cos(meepleAngle))};
        meeple[i].Init();
    }

    srand(time(0));         //just to get random colors

    for(uint8_t i=0;i<XTerrain;i++){
        for(uint8_t j=0;j<ZTerrain;j++){
            terrain[i][j].color[0]=(rand()%1000)/1000.0f;
            terrain[i][j].color[1]=(rand()%1000)/1000.0f;
            terrain[i][j].color[2]=(rand()%1000)/1000.0f;
            terrain[i][j].noSound=true;
            terrain[i][j].ModelFile="models/cube.glb";
            terrain[i][j].position={XTerrain-1-(float)2*i,-1.0f,ZTerrain-1-(float)2*j};
            terrain[i][j].Init();
        }
    }

    


    // *****************  main program **************************

    std::thread th1(RotateMeeples);
    
    RenderLoop();
    
    // *********************** end **********************

    Sound_DeleteListener();
    Yave_End();
	return 0;
}


void RenderLoop(void){
    while (YAVE_activeWindow())
    {
        YAVE_executeEvents();
        YAVE_prepareRender();

        UpdateListener();
        for(int i=0;i<numberOfMeeples;i++){
            meeple[i].Render();
        }

        for(uint8_t i=0;i<XTerrain;i++){
            for(uint8_t j=0;j<ZTerrain;j++){
                terrain[i][j].Render();
            }
        }

    }
}

void RotateMeeples(void){
    while(1){
        auto nowt=std::chrono::high_resolution_clock::now();
        auto deltat = std::chrono::duration_cast<std::chrono::milliseconds>(nowt - lastt);
        
        if( deltat.count() >= dt){
        for(int i=0;i<numberOfMeeples;i++){
            double angle = 2*3.14/numberOfMeeples*i+2*3.14*totalCount*dt/Period;
            meeple[i].position[0] = distanceOfMeeples * sin(angle);
            meeple[i].position[2] = distanceOfMeeples * cos(angle);
        }
        totalCount++;
        if(2*3.14*totalCount*dt/Period>=Period){
            totalCount=0;
        }
        lastt= std::chrono::high_resolution_clock::now();
        }
    }
}