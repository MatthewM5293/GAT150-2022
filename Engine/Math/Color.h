#pragma once
#include <cstdint>
#include<iostream>
#include <string>

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

		uint8_t operator [] (size_t index) const { return (&r)[index]; } //(index == 0) ? x : y; }
		uint8_t& operator [] (size_t index) { return (&r)[index]; } //(index == 0) ? x : y; }


		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;

		friend std::istream& operator >> (std::istream& stream, Color& c);
		friend std::ostream& operator << (std::ostream& stream, const Color& color);
	};

	
	std::istream& operator >> (std::istream& stream, Color& c);
	std::ostream& operator << (std::ostream& stream, const Color& color);
	
}