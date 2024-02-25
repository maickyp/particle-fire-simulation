#ifndef SCREEN_H_
#define SCREEN_H_

#include "SDL2/SDL.h"

namespace custom_sdl_screen{

    #define RED_CHANNEL_MASK    0xFF000000
    #define GREEN_CHANNEL_MASK  0x00FF0000
    #define BLUE_CHANNEL_MASK   0x0000FF00
    #define ALPHA_CHANNEL_MASK  0x000000FF

    #define RED_CHANNEL_SHIFT   24
    #define GREEN_CHANNEL_SHIFT 16
    #define BLUE_CHANNEL_SHIFT  8
    #define ALPHA_CHANNEL_SHIFT 0

    class Screen{
        private:
            SDL_Window *m_Window;
            SDL_Renderer *m_renderer;
            SDL_Texture *m_texture;
            Uint32* m_buffer;
            Uint32* m_auxBuffer;

        public:
        static const int SCREEN_WIDTH = 1080;
        static const int SCREEN_HEIGHT = 720;

            Screen();
            ~Screen();

            int init();
            bool close();

            void updateScreen();
            bool processEvents();
            void clear();
            void boxBlur();

            void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

    };

} /* namespace custom_sd_screen*/

#endif /* SCREEN_H_ */