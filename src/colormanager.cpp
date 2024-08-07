#include "colormanager.h"

Color sand{ 254, 237, 192, 255 };
Color water{ 117, 149, 224, 255 };
Color stone{ 200, 200, 200, 255 };
Color lava{ 231, 111, 81, 255 };
Color smoke{ 200, 200, 200, 100 };
Color cement{ 230,230,230,255 };
Color acid{ 105, 235, 101, 255 };
Color oil{ 33, 32, 46 , 255 };
Color fire{ 231, 111, 81, 255 };
Color gunpowder{ 40,40,40,255 };

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

void ColorManager::elementColor(int y, int x, int type)
{
	if (type == 1)
	{
		Color sand{
			(unsigned char)GetRandomValue(240, 255),
			(unsigned char)GetRandomValue(200, 237),
			(unsigned char)GetRandomValue(180, 195),
			255
		};
		setColor(y, x, sand);
	}
	else if (type == 2)
	{
		Color water{ 117, 149, 224, 255 };
		setColor(y, x, water);
	}
	else if (type == 3)
	{
		Color stone{
			170,
			170,
			170,
			(unsigned char)GetRandomValue(150,255)
		};
		setColor(y, x, stone);
	}
	else if (type == 4)
	{
		Color lava{
			(unsigned char)GetRandomValue(220,231),
			(unsigned char)GetRandomValue(100,111),
			81,
			255 };
		Color temp_lava = lava;
		temp_lava.r += GetRandomValue(-10, 10);
		temp_lava.g += GetRandomValue(-10, 10);

		setColor(y, x, temp_lava);
	}
	else if (type == 5)
	{
		Color smoke{
			128,
			128,
			128,
			(unsigned char)GetRandomValue(0, 100) };
		setColor(y, x, smoke);
	}
	else if (type == 6)
	{
		setColor(y, x, cement);
	}
	else if (type == 7)
	{
		setColor(y, x, acid);
	}
	else if (type == 8)
	{
		setColor(y, x, oil);
	}
	else if (type == 9)
	{
		setColor(y, x, fire);
	}
	else if (type == 10)
	{
		Color gunpowder{
			40,
			40,
			40,
			(unsigned char)GetRandomValue(200,255) };
		setColor(y, x, gunpowder);
	}
}

Color ColorManager::getElementColor(int type)
{
	switch (type)
	{
	case 1: return sand;
	case 2: return water;
	case 3: return stone;
	case 4: return lava;
	case 5: return smoke;
	case 6: return cement;
	case 7: return acid;
	case 8: return oil;
	case 9: return fire;
	case 10: return gunpowder;
	default: return BLANK;
	}
}
