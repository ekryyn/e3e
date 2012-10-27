#include "Matrix4fStack.hpp"

e3e::Matrix4fStack::Matrix4fStack()
{
	push();
}

void e3e::Matrix4fStack::push()
{
	e3e::Matrix4f *toPush = isEmpty() ? new e3e::Matrix4f() : new e3e::Matrix4f(*top());
	data.push_back(toPush);
}

void e3e::Matrix4fStack::pop()
{
	if(!isEmpty())
	{
		e3e::Matrix4f *b = data.back();
		data.pop_back();
		delete b;
	}
}

void e3e::Matrix4fStack::translate(float x, float y, float z)
{
	e3e::Matrix4f t = e3e::Matrix4f::translation(x, y, z);
	(*top()) *= t;
}

void e3e::Matrix4fStack::replace(const Matrix4f &newTransformation)
{
	(*top()) = e3e::Matrix4f(newTransformation);
}

void e3e::Matrix4fStack::transform(const Matrix4f &transformation)
{
	(*top()) *= transformation;
}
