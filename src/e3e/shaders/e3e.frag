smooth in vec3 normal0;
in vec2 uvCoord0;

uniform vec4 diffuseColor;
uniform sampler2D tex;
uniform bool textureIsActive;
uniform float textureDiffuseInfluence;

out vec4 outputColor;
in vec3 lightDirection0;

void main(void)
{
	vec4 lightColor = vec4(1,1,1,1);
	vec4 ambiantColor = vec4(1,1,1,1);
	float ambiantFactor = .0;

	float diffuseFactor = dot( (normal0), -lightDirection0 );

	vec4 diffuseLightColor;

	if (diffuseFactor > 0) {
		diffuseLightColor = lightColor * diffuseFactor;
	}
	else {
		diffuseLightColor = vec4(0, 0, 0, 0);
	}

	vec4 colorToApply;
	if(textureIsActive) {
		colorToApply += (1-textureDiffuseInfluence)*diffuseColor;
		colorToApply += (textureDiffuseInfluence)*(texture2D(tex, uvCoord0.st));
	} else {
		colorToApply = diffuseColor;
	}

	outputColor = colorToApply * diffuseLightColor;
}
