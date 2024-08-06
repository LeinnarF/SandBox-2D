#pragma once
#include <vector>
#include <raylib.h>

class ColorManager
{
public:
	ColorManager(int width, int height);

	void setColor(int y, int x, Color color);
	Color getColor(int y, int x) const;
	void resetColors();

	void elementColor(int y, int x, int type);

private:
	int m_width;
	int m_height;
	std::vector<std::vector<Color>> m_colors;
};