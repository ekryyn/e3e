uniform mat4 projectionMatrix;
uniform mat4 worldTransformMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

flat out vec4 frontColor;

void main()
{
	frontColor = color;

	vec4 temp = worldTransformMatrix * position;
	temp = projectionMatrix * temp;

	gl_Position = temp;
}
