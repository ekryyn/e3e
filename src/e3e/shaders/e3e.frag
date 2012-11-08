smooth in vec4 frontColor;

smooth in vec3 normal0;
in vec2 uvCoord0;

uniform sampler2D tex;

out vec4 outputColor;
in vec3 lightDirection0;

void main(void)
{
	vec4 lightColor = vec4(1,1,1,1);
	vec4 ambiantColor = vec4(1,1,1,1);
	float ambiantFactor = .0;

	float diffuseFactor = dot( (normal0), -lightDirection0 );

	vec4 diffuseColor;

	if (diffuseFactor > 0) {
		diffuseColor = lightColor * diffuseFactor;
	}
	else {
		diffuseColor = vec4(0, 0, 0, 0);
	}

	outputColor = texture2D(tex, uvCoord0.st) * diffuseColor;
	outputColor += texture2D(tex, uvCoord0.st) * ambiantColor * ambiantFactor; // add a bit of initial color (avoid black for now)

//	outputColor = texture2D(tex, uvCoord0.st);

	if(normal0 == vec3(0,0,0))
	{
		outputColor = frontColor;
	}
//	outputColor = frontColor;

}
