#version 330

struct Lights {
  vec3 position;
  vec3 color;
  float brightness;
  float range;
};

uniform Lights lights[];

// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// From vertex Shader
in vec2 texCoord;

in vec3 normalVec3;
in vec4 normalVec4;

in vec3 FragPosition;
in vec3 FragPositionS;


// The final color
out vec4 FragmentColor;

void main() {

  float diffuse = max(dot(normalVec4, vec4(normalize(LightDirection), 1.0f)), 0.0f);

  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
  //FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * diffuse;
  FragmentColor = vec4(lights[0].color.x,lights[0].color.y,lights[0].color.z,0.0);
  FragmentColor.a = Transparency;
}
