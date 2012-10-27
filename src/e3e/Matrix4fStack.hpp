#ifndef MATRIX4FSTACK_HPP
#define MATRIX4FSTACK_HPP

#include <vector>

#include "Matrix4f.hpp"

namespace e3e
{

class Matrix4fStack
{
public:
	Matrix4fStack();

	inline bool isEmpty() const { return data.empty(); }
	inline Matrix4f* top() const { return data.back(); }

	void push();
	void pop();

	void translate(float x, float y, float z);
	void replace(const Matrix4f &newTransformation);

private:
	std::vector<Matrix4f*> data;
};

}

#endif // MATRIX4FSTACK_HPP
