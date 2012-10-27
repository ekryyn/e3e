#ifndef MATRIX4F_HPP
#define MATRIX4F_HPP

namespace e3e
{

class Matrix4f
{
public:
	// identity
	Matrix4f();

	Matrix4f(float a1, float a2, float a3, float a4,
				float b1, float b2, float b3, float b4,
				float c1, float c2, float c3, float c4,
				float d1, float d2, float d3, float d4);

	Matrix4f& operator *= (const Matrix4f& m);
	Matrix4f operator* (const Matrix4f& m) const;

	static Matrix4f translation(float x, float y, float z);

	static Matrix4f rotationX(float r);
	static Matrix4f rotationY(float r);
	static Matrix4f rotationZ(float r);

	float* createColumnMajorArray() const;

	float a1, a2, a3, a4;
	float b1, b2, b3, b4;
	float c1, c2, c3, c4;
	float d1, d2, d3, d4;

};

}

#endif // MATRIX4F_HPP
