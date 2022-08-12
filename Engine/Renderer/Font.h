#pragma once
#include "Resource/Resource.h"
#include <string>
 
// !! forward declare the _TTF_Font struct 
struct _TTF_Font;

namespace neu
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(const std::string& filename, void* data = nullptr) override;// { return false; }
		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		_TTF_Font* m_ttfFont{ nullptr };
	};
}