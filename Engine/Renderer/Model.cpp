#include "Model.h"
#include "../Core/File.h"

#include <iostream>
#include <sstream>

namespace neu  
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float& angle, float& scale)
	{
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	void Model::Load(const std::string& filename)
	{
		std::string buffer;

		neu::ReadFile(filename, buffer);
		std::istringstream stream(buffer);
		
		//read color
		stream >> m_color;

		//m_color.r = 255;
		//m_color.g = 255;
		//m_color.b = 255;
		//m_color.a = 255;

		std::string line;
		std::getline(stream, line);

		//get number of points
		size_t numPoints = std::stoi(line);

		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
			

		}
		
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		//find by the largest length
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}
}