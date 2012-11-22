#ifndef EVECTOR2_HPP
#define EVECTOR2_HPP

namespace e3e
{

class Vector2d
{
public:
	Vector2d();
	Vector2d(double x, double y);
	Vector2d(const Vector2d& v);

	double x;
	double y;

	Vector2d & operator= (const Vector2d & v);

	Vector2d & operator+= (const Vector2d & v);
	Vector2d operator+ (const Vector2d & v) const;

	Vector2d & operator-= (const Vector2d & v);
	Vector2d operator- (const Vector2d & v) const;

	Vector2d & operator*= (const double a);
	Vector2d operator* (const double a)const;
	friend Vector2d operator* (const double a,const Vector2d & v);

	Vector2d & operator/= (const double a);
	Vector2d operator/ (const double a)const;

	double length() const;
	void normalize();
};


}

#endif // EVECTOR2_HPP
