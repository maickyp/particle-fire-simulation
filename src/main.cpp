#include <iostream>
#include "SDL2/SDL.h"
#include "screen.h"
#include "swarm.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv){
    srand(time(NULL));
    custom_sdl_screen::Screen mainScreen;

    int ret = mainScreen.init();

    if( ret < 0){
        std::cout<< "Failed to init: "<< ret<< std::endl;
    }

    int halfWidth = mainScreen.SCREEN_WIDTH /2;
    int halfHeight = mainScreen.SCREEN_HEIGHT/2;

    custom_sdl_screen::Swarm swarm;
    const custom_sdl_screen::Particle * const pParticles = swarm.getParticles();
    while(true){

        // Doing some cool stuff

        // presets
        // mainScreen.clear();
        unsigned int timeElapsed = SDL_GetTicks();
        swarm.update(timeElapsed);

        // Shifting colors
        unsigned char red = (unsigned char)((1+cos(timeElapsed*0.0002)) * 128);
        unsigned char green = (unsigned char)((1+sin(timeElapsed*0.0002)) * 128);
        unsigned char blue = (unsigned char)((1+sin(timeElapsed*0.0003)) * 128);

        for (int i=0; i<custom_sdl_screen::Swarm::NPARTICLES; i++){

            custom_sdl_screen::Particle particle= pParticles[i];

            int x = (particle.m_x + 1) * halfWidth;
            int y = particle.m_y * halfWidth + halfHeight;

            mainScreen.setPixel(x, y, red, green, blue);
        }

        mainScreen.boxBlur();
        mainScreen.updateScreen();

        if(mainScreen.processEvents() != true){
            break;
        }
    }

    if(mainScreen.close() == false){
        std::cout << "Failed to deinit" << std::endl;
    }

    return 0;
};

