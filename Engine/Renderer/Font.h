#pragma once
#include <string>
// !! add necessary includes 
 
// !! forward declare the _TTF_Font struct 
struct _TTF_Font;

namespace neu
{
	class Font
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		_TTF_Font* m_ttfFont{ nullptr };
	};
}