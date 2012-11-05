smooth in vec4 frontColor;

smooth in vec3 normal0;

out vec4 outputColor;

void main(void)
{
	vec4 lightColor = vec4(1,1,1,1);
	vec3 lightDirection = vec3(-1,-1,-1);

	float diffuseFactor = dot( (normal0), -lightDirection );

	vec4 diffuseColor;

	if (diffuseFactor > 0) {
		diffuseColor = lightColor * diffuseFactor;
	}
	else {
		diffuseColor = vec4(0, 0, 0, 0);
	}


	outputColor = frontColor * diffuseColor;
	outputColor += (frontColor/2); // add a bit of initial color (avoid black for now)

	if(normal0 == vec3(0,0,0))
	{
		outputColor = frontColor;
	}
}
