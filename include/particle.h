#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <stdlib.h>

namespace custom_sdl_screen{

    struct Particle{
        double m_x;
        double m_y;

        double m_speed;
        double m_direction;

        public:
        Particle();
        virtual ~Particle();
        void update(unsigned int interval);
        void init();
        void setPos(double x, double y);
    };

}; /* namespace custom_sd_screen*/


#endif
