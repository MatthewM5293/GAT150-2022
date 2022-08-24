#include "Font.h" 
#include <SDL_ttf.h> 

namespace neu
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont) 
		{
			TTF_CloseFont(m_ttfFont); //?????
			m_ttfFont = nullptr;
		}
	}

	bool Font::Create(std::string filename, ...)
	{
		//Load(filename, 22);
		va_list args;

		va_start(args, filename);

		int fontSize = va_arg(args, int);

		va_end(args);

		Load(filename, fontSize);
		return true;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize); //??
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c = *((SDL_Color*)(&color));
		SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

		if (surface == nullptr)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}
}