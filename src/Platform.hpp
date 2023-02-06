#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Platform {
    public:
        ~Platform();
        Platform(char const *title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
        void Update(void const *buffer, int pitch);
        bool ProcessInput(uint8_t *keys);
    
        SDL_Window *window{};
        SDL_Renderer *renderer{};
        SDL_Texture *texture{};
};