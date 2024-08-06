#include "colormanager.h"

ColorManager::ColorManager(int width, int height) :
	m_width(width),
	m_height(height),
	m_colors(height, std::vector<Color>(width, BLANK))
{}

void ColorManager::setColor(int y, int x, Color color)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		m_colors[y][x] = color;
	}
}

Color ColorManager::getColor(int y, int x) const
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		return m_colors[y][x];
	}
	return RED; // Idk? for debugging?
}

void ColorManager::resetColors()
{
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			m_colors[y][x] = BLANK;
		}
	}
}

void ColorManager::elementColor(int y, int x, int target)
{
	if (target == 1)
	{
		Color sand = {
			(unsigned char)GetRandomValue(240, 255),
			(unsigned char)GetRandomValue(200, 237),
			(unsigned char)GetRandomValue(180, 195),
			255
		};
		setColor(y, x, sand);
	}
	else if (target == 3)
	{
		Color stone = {
			170,
			170,
			170,
			(unsigned char)GetRandomValue(220,255)
		};
		setColor(y, x, stone);
	}
}
