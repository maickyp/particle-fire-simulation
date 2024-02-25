#include "screen.h"
#include "Windows.h"
#include <iostream>

namespace custom_sdl_screen{

    Screen::Screen() : m_Window(nullptr), m_renderer(nullptr), m_texture(nullptr), m_buffer(nullptr), m_auxBuffer(nullptr){
    };
    int Screen::init(){

        if ( ( SDL_Init(SDL_INIT_VIDEO) < 0 ) ){
            std::cout << "SDL initialization was not succeeded" << std::endl;
            return -1;
        }

        m_Window = SDL_CreateWindow("Particle Fire Explosion",
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
        if(m_Window == nullptr){
            std::cout << "Error creating window." << SDL_GetError();
            SDL_Quit();
            return -2;
        }

        m_renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
        if(m_renderer == NULL){
            std::cout << "Error creating renderer." << SDL_GetError();
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            return -3;
        }

        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

        if(m_texture == NULL){
            std::cout << "Error creating textures." << SDL_GetError();
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            return -4;
        }

        m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        m_auxBuffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

        memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        memset(m_auxBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

        return true;
    };

    void Screen::updateScreen(){
        SDL_UpdateTexture(m_texture,NULL, m_buffer, SCREEN_WIDTH*sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    void Screen::clear(){
        memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        memset(m_auxBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    }

    bool Screen::processEvents(){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                return false;
            }
        }
        return true;
    };

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){

        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
            return;

        Uint32 color = 0;

        color += (red << RED_CHANNEL_SHIFT);
        color += (green << GREEN_CHANNEL_SHIFT);
        color += (blue << BLUE_CHANNEL_SHIFT);
        color += (0xFF << ALPHA_CHANNEL_SHIFT);

        m_buffer[(y*SCREEN_WIDTH)+x] = color;
    }

    bool Screen::close(){
        delete [] m_buffer;
        delete [] m_auxBuffer;
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return true;
    };

    Screen::~Screen(){

    };

    void Screen::boxBlur(){

        Uint32 *temp = m_buffer;
        m_buffer = m_auxBuffer;
        m_auxBuffer = temp;

        for(int y=0; y<SCREEN_HEIGHT; y++) {
        	for(int x=0; x<SCREEN_WIDTH; x++) {

        		int redTotal=0;
        		int greenTotal=0;
        		int blueTotal=0;

        		for(int row=-1; row<=1; row++) {
        			for(int col=-1; col<=1; col++) {
        				int currentX = x + col;
        				int currentY = y + row;

        				if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
        					Uint32 color = m_auxBuffer[currentY*SCREEN_WIDTH + currentX];

        					Uint8 red = color >> RED_CHANNEL_SHIFT;
        					Uint8 green = color >> GREEN_CHANNEL_SHIFT;
        					Uint8 blue = color >> BLUE_CHANNEL_SHIFT;

        					redTotal += red;
        					greenTotal += green;
        					blueTotal += blue;
        				}
        			}
        		}

        		Uint8 red = redTotal/9;
        		Uint8 green = greenTotal/9;
        		Uint8 blue = blueTotal/9;

        		setPixel(x, y, red, green, blue);
        	}
        }
    };


} // namespace custom_sdl_screen


