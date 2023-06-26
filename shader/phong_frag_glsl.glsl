#version 330

struct Lights {
    float type;
    vec3 position;
    vec3 color;
    float brightness;
    vec3 direction;
};

uniform float Lights_count;
uniform Lights lights[20];  // need const and I cant use Lights_count, increase if more than 20 lights (doubt it tbh)


// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of directional-light
uniform vec3 LightDirection;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

//material properties
uniform float materialShininess;
uniform float materialDiffuse;
uniform float materialSpecular;

uniform mat4  ViewMatrix;

uniform vec3 ViewPosition;

// From vertex Shader
in vec2 texCoord;

in vec3 normalVec3;
in vec4 normalVec4;

in vec3 FragPosition;
in vec3 FragPositionS;


// The final color
out vec4 fragColor;

vec3 pointLight(Lights light, vec3 normalVec3, vec3 fragPos, vec3 viewDir);
vec3 directionalLight(vec3 lightDirection, vec3 normalVec3, vec3 viewDir);
vec3 spotLight(Lights light, vec3 normalVec3, vec3 fragPos, vec3 viewDir);

void main() {

    //float diffuse = max(dot(normalVec4, vec4(normalize(LightDirection), 1.0f)), 0.0f);

    // Lookup the color in Texture on coordinates given by texCoord
    // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ



    vec3 viewDirection = normalize(ViewPosition - FragPosition);


    vec4 FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset);

    vec3 result;

    result = directionalLight(LightDirection, normalVec3, viewDirection); //Directional

    for(int i = 0; i <= Lights_count; i++){
        if(lights[i].type == 0){ //Point
            result += pointLight(lights[i], normalVec3, FragPosition, viewDirection);
        }
        if(lights[i].type == 1){ //Spot
            result += spotLight(lights[i], normalVec3, FragPosition, viewDirection);
        }

    }

    fragColor = vec4(result, 1.0) * FragmentColor ;
    //fragColor = vec4(result, 1.0) ; // lightmap for debugging
}

float lightConstant = 1.0;
float lightLinear= 0.01;
float lightQuadratic = 0.003;
vec3 lightAmbient = vec3(0.9f,0.9f,0.9f);
vec3 lightDiffuse = vec3(0.5f,0.5f,0.5f);
vec3 lightSpecular = vec3(0.7f,0.7f,0.7f);

//float materialShininess = 32;
//float materialDiffuse = 1;
//float materialSpecular = 1;

float directionalLightIntensity = 0.1; // very low;
vec3 directionalLightColor = vec3(1,1,1);

float spotLightCutOff = 15.0f;
float spotLightOuterCutOff = 25.0f;

float PI = 3.141592;



vec3 pointLight(Lights light, vec3 normalVec3, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normalVec3, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normalVec3);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);// last part here is material-shininess if we want to add it

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    //combine the 3:
    vec3 ambient = lightAmbient * light.color * light.brightness * materialDiffuse;
    vec3 diffuse = lightDiffuse * diff * light.color * light.brightness * materialDiffuse;
    vec3 specular = lightSpecular * spec * light.color * light.brightness * materialSpecular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);


}
vec3 directionalLight(vec3 lightDirection, vec3 normalVec3, vec3 viewDir){

    float diff = max(dot(normalVec3, lightDirection), 0.0);

    vec3 reflectDir = reflect(-lightDirection, normalVec3);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);// last part here is material-shininess if we want to add it

    //combine the 3:
    vec3 ambient = lightAmbient * directionalLightColor * materialDiffuse;
    vec3 diffuse = lightDiffuse * diff * directionalLightColor * materialDiffuse;
    vec3 specular = vec3(0);

    return (normalize(ambient + diffuse + specular) * directionalLightIntensity);
}

vec3 spotLight(Lights light, vec3 normalVec3, vec3 fragPos, vec3 viewDir){


    /*vec3 toFragDir = normalize(light.position - FragPosition);

    float diff = max(dot(normalVec3, toFragDir), 0.0);

    vec3 reflectDir = reflect(-toFragDir, normalVec3);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);

    float distance = length(light.position - FragPosition);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    vec3 spotLightDirection = light.position * light.direction;

    float theta = dot(spotLightDirection, toFragDir);
    float epsilon = spotLightCutOff - spotLightOuterCutOff;
    float intensity = clamp((spotLightOuterCutOff - theta) / epsilon , 0.0, 1.0);


    float dotProduct = dot(LightDirection, toFragDir);

    // Calculate the lengths of the two vectors
    float LightDirectionLength = sqrt(LightDirection.x * LightDirection.x + LightDirection.y * LightDirection.y + LightDirection.z * LightDirection.z);
    float toFragDirLength = sqrt(toFragDir.x * toFragDir.x + toFragDir.y * toFragDir.y + toFragDir.z * toFragDir.z);

    // Calculate the angle between the two vectors using the dot product and vector lengths
    float angle = acos(dotProduct / (LightDirectionLength * toFragDirLength));

    //combine the 3:
    vec3 ambient  = vec3(0,0,0);
    vec3 diffuse  = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);

    if(angle < 45 - spotLightOuterCutOff){
        ambient  = lightAmbient            * light.color * light.brightness * materialDiffuse;
        diffuse  = lightDiffuse    * diff  * light.color * light.brightness * materialDiffuse;
        specular = lightSpecular   * spec  * light.color * light.brightness * materialSpecular;


        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
    }



    return (ambient + diffuse + specular);*/

    vec3 toFragDir = normalize(light.position - FragPosition);

    float diff = max(dot(normalVec3, toFragDir), 0.0);

    vec3 reflectDir = reflect(-toFragDir, normalVec3);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);

    float distance = length(light.position - FragPosition);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    vec3 lightTo = light.position + light.direction;

    vec3 spotlightDirection = light.position - lightTo;

    float dotProduct = dot(spotlightDirection, toFragDir);
    float angleInRadians = acos(dotProduct / (length(spotlightDirection) * length(toFragDir)));
    float angleInDegrees = angleInRadians * (180 / PI);

    vec3 ambient  = vec3(0,0,0);
    vec3 diffuse  = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);

    if(angleInDegrees < spotLightOuterCutOff){
        ambient  = lightAmbient            * light.color * light.brightness * materialDiffuse;
        diffuse  = lightDiffuse    * diff  * light.color * light.brightness * materialDiffuse;
        specular = lightSpecular   * spec  * light.color * light.brightness * materialSpecular;


        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        if(angleInDegrees > spotLightCutOff){
            ambient *= ((spotLightOuterCutOff - angleInDegrees) / (spotLightOuterCutOff - spotLightCutOff)) ;
            diffuse *= ((spotLightOuterCutOff - angleInDegrees) / (spotLightOuterCutOff - spotLightCutOff));
            specular *= ((spotLightOuterCutOff - angleInDegrees) / (spotLightOuterCutOff - spotLightCutOff));
        }
    }

    return (ambient + diffuse + specular);
}
