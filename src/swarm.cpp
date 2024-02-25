#include "swarm.h"

namespace custom_sdl_screen{

Swarm::Swarm(){
    m_pParticles = new Particle[NPARTICLES];
}

Swarm::~Swarm(){
    delete [] m_pParticles;
}

void Swarm::update(unsigned int ticks){

    unsigned int interval = ticks - lastUpdate;

    for (int i=0; i<custom_sdl_screen::Swarm::NPARTICLES; i++){
        m_pParticles[i].update(interval);
    }

    lastUpdate = ticks;
}

}; /* namespace custom_sd_screen*/
