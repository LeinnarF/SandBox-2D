#include "colormanager.h"
#include "elementEnum.h"

//TODO: add here
Color sandColor{ 254, 237, 192, 255 };
Color waterColor{ 117, 149, 224, 255 };
Color stoneColor{ 200, 200, 200, 255 };
Color lavaColor{ 231, 111, 81, 255 };
Color smokeColor{ 200, 200, 200, 100 };
Color cementColor{ 230,230,230,255 };
Color acidColor{ 105, 235, 101, 255 };
Color oilColor{ 33, 32, 46 , 255 };
Color fireColor{ 231, 111, 81, 255 };
Color gunpowderColor{ 40,40,40,255 };
Color woodColor = BROWN; // TODO: change this!

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
	//TODO: add here
	switch (type)
	{
	case sand:
	{
		Color sand{
			(unsigned char)GetRandomValue(240, 255),
			(unsigned char)GetRandomValue(200, 237),
			(unsigned char)GetRandomValue(180, 195),
			255
		};
		setColor(y, x, sand);
		break;
	}
	case water:
	{
		Color water{ 117, 149, 224, 255 };
		setColor(y, x, water);
		break;
	}
	case stone:
	{
		Color stone{
			170,
			170,
			170,
			(unsigned char)GetRandomValue(150, 255)
		};
		setColor(y, x, stone);
		break;
	}
	case lava:
	{
		Color temp_lava = lavaColor;
		temp_lava.r += GetRandomValue(-10, 10);
		temp_lava.g += GetRandomValue(-10, 10);

		setColor(y, x, temp_lava);
		break;
	}
	case smoke:
	{
		Color smoke{
			128,
			128,
			128,
			(unsigned char)GetRandomValue(0, 100)
		};
		setColor(y, x, smoke);
		break;
	}
	case cement:
	{
		setColor(y, x, cementColor);
		break;
	}
	case acid:
	{
		setColor(y, x, acidColor);
		break;
	}
	case oil:
	{
		setColor(y, x, oilColor);
		break;
	}
	case fire:
	{
		Color randColor = (GetRandomValue(0, 20) == 1) ? YELLOW : fireColor;
		setColor(y, x, randColor);
		break;
	}
	case gunpowder:
	{
		Color gunpowder{
			40,
			40,
			40,
			(unsigned char)GetRandomValue(200, 255)
		};
		setColor(y, x, gunpowder);
		break;
	}
	case wood:
	{
		setColor(y, x, woodColor);
	}
	default:
		break;
	}
}

Color ColorManager::getElementColor(int type)
{
	// TODO: add here
	switch (type)
	{
	case sand: return sandColor;
	case water: return waterColor;
	case stone: return stoneColor;
	case lava: return lavaColor;
	case smoke: return smokeColor;
	case cement: return cementColor;
	case acid: return acidColor;
	case oil: return oilColor;
	case fire: return fireColor;
	case gunpowder: return gunpowderColor;
	case wood: return woodColor;
	default: return BLANK;
	}
}
