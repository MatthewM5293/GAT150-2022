#include "Math/Color.h"

namespace neu
{
	const Color Color::white{255, 255, 255, 255};
	const Color Color::black{0, 0, 0, 255};
	const Color Color::red{255, 0, 0, 255};
	const Color Color::green{0, 255, 0, 255};
	const Color Color::blue{0, 0, 255, 255};

	std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;

		// { ##, ##, ## }
		//get red
		str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		c.r = (uint8_t)(std::stof(str) * 255);

		//get green
		str = line.substr(line.find(",") + 1, line.find_last_of(",") - line.find(",") - 1);
		c.g = (uint8_t)(std::stof(str) * 255);

		//get blue
		str = line.substr(line.find_last_of(",") + 1, line.find("}") - line.find_last_of(",") - 1);
		c.b = (uint8_t)(std::stof(str) * 255);

		c.a = 255;

		return stream;
	}
}