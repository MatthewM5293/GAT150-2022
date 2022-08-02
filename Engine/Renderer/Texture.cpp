#include "Texture.h" 
#include "Renderer.h" 
#include <SDL.h> 
#include <SDL_image.h> 

namespace neu
{
    Texture::~Texture()
    {
        // !! if texture not null SDL_DestroyTexture 
        if (m_texture != NULL)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename)
    {
        // load surface 
        SDL_Surface* surface = IMG_Load(filename.c_str());// !! call IMG_Load with c-string of filename 

        // create texture 
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface 
            // !! the first parameter takes in the m_renderer from renderer 
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
            // !! call SDL_FreeSurface with surface as the parameter 
        SDL_FreeSurface(surface);
            // !! no need to keep surface after texture is created 

            return true;
    }

    neu::Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        //pass address of x and y
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

        return Vector2(point.x, point.y);// !! return Vector2 of point.x, point.y 
    }
}
