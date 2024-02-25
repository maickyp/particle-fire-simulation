#ifndef SWARM_H_
#define SWARM_H_

#include "particle.h"

    namespace custom_sdl_screen{
    class Swarm{
        private:
            Particle *m_pParticles;
        public:
            const static int NPARTICLES = 1000;
            unsigned int lastUpdate;

        public:
            Swarm();
            ~Swarm();
            void update(unsigned int ticks);
            const Particle* const getParticles(){ return m_pParticles;};
    };

}


#endif
