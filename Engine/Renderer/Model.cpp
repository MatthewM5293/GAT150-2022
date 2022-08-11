#include "Model.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Math/Transform.h"

#include <iostream>
#include <sstream>

namespace neu  
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	bool Model::Create(const std::string& filename)
	{
		if (!Load(filename))
		{
			LOG("ERROR could not create model %s", filename.c_str());
			return false;
		}

		return true;
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
	{
		//draw points
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Matrix3x3 mx = transform.matrix;
		//if (m_points.size() == 0) return;

		for (int i = 0; i < m_points.size() - 1; i++)
		{

			neu::Vector2 p1 = mx * m_points[i];
			neu::Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	bool Model::Load(const std::string& filename)
	{
		std::string buffer;

		if (!neu::ReadFile(filename, buffer))
		{
			LOG("Error could not load file %s", filename.c_str());
			return false;
		}


		std::istringstream stream(buffer);
		//read color
		stream >> m_color;

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
		return true;
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