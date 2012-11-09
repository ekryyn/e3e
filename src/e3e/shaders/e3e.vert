uniform float time;
uniform mat4 projectionMatrix;
uniform mat4 worldTransformMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvCoord;

smooth out vec4 diffuseColor0;
smooth out vec3 normal0;
out vec2 uvCoord0;

out vec3 lightDirection0;

void main()
{

	vec4 temp = worldTransformMatrix * position;
	temp = projectionMatrix * temp;

	gl_Position = temp;

	vec4 n = (worldTransformMatrix * vec4(normal, 0));
	normal0 = n.xyz;

	vec3 lightDirection = vec3(cos(time), -sin(time), -.5);
	vec4 ld = (worldTransformMatrix * vec4(lightDirection, 0));

	lightDirection0 = ld.xyz;

	uvCoord0 = uvCoord;
}
