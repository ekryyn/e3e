#ifndef COLOR_HPP
#define COLOR_HPP

namespace e3e
{

class Color
{
public:
	Color();
	Color(float r, float g, float b, float a = 1.f);

	float r, g, b, a;
private:
};

}
#endif // COLOR_HPP
