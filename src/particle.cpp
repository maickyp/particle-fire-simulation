#include "particle.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
// #include <math.h>

// #define M_PI 3.14159265
#include <stdlib.h>
namespace custom_sdl_screen{

Particle::Particle() {
    init();
}

Particle::~Particle(){

}

void Particle::init(){
    m_x=0;
    m_y=0;
    m_direction = (2 * M_PI * rand())/RAND_MAX;
    m_speed = (0.1 * rand())/RAND_MAX;

    m_speed *= m_speed;
}

void Particle::setPos(double x, double y){
    m_x = x;
    m_y = y;
}

void Particle::update(unsigned int interval){

    // m_direction += interval * 0.005; // Curling explosion

    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    m_x += xspeed * interval;
    m_y += yspeed * interval;

    if( m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1){
        init();
    }
}

}; /* namespace custom_sd_screen*/
