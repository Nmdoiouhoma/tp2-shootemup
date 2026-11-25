module;
#include <SDL3/SDL.h>

export module sdl;

import std;

export namespace shootemup {


    class SdlContext  {
    public:
        SdlContext() {
            if (!SDL_Init(SDL_INIT_VIDEO)) {
                throw std::runtime_error{SDL_GetError()};
            }
        }
        ~SdlContext()  {
            SDL_Quit();
        }

        SdlContext(const SdlContext&) = delete;
        SdlContext& operator=(const SdlContext& context) = delete;

    };

}
