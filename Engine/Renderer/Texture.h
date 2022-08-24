#pragma once 
#include "Math\Vector2.h" 
#include "Resource/Resource.h"
#include <string> 
 
struct SDL_Texture; 
struct SDL_Surface;
namespace neu
{ 
	class Renderer;
	class Texture : public Resource
	{
public:
	Texture() = default;
	~Texture();

	bool Create(std::string filename, ...) override;

	bool Create(Renderer& renderer, const std::string& filename);
	bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

	Vector2 GetSize() const;

	friend class Renderer;

private:
	SDL_Texture* m_texture = nullptr;
	};
}