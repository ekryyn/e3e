uniform mat4 projectionMatrix;
uniform mat4 worldTransformMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

flat out vec4 frontColor;

void main()
{
	frontColor = color;

	// testing if color is defined
	if(color == vec4(0,0,0,1)){
		frontColor = vec4(1,0,1,1);
	}

	vec4 temp = worldTransformMatrix * position;
	temp = projectionMatrix * temp;

	gl_Position = temp;
}
