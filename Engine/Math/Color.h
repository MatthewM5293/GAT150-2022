#pragma once
#include <cstdint>

namespace neu
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char; //alternative

	struct Color 
	{
		//unsigned char r;
		uint8_t r; //C version
		uint8_t g; 
		uint8_t b; 
		uint8_t a; 

		friend std::istream& operator >> (std::istream& stream, Color& c);
	};

	
	inline std::istream& operator >> (std::istream& stream, Color& c)
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