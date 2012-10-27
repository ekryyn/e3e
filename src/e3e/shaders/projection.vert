uniform mat4 projectionMatrix;
uniform mat4 worldTransformMatrix;

void main()
{
	gl_FrontColor = gl_Color;

	vec4 temp = worldTransformMatrix * gl_Vertex;
	temp = projectionMatrix * temp;

	gl_Position = temp;
}
