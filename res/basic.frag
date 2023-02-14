#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

struct Spotlight 
{
    vec3 direction;
    vec3 position;
    float innerCutoff;
    float outerCutoff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Spotlight uSpotlight; 

struct DirectionalLight 
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight uDirLight;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material uMaterial;
uniform vec3 uViewPosition;

vec3 calculateSpotlight(Spotlight light, vec3 normal, vec3 viewDir)
{
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(normalize(light.direction), -lightDir);
    float intensity = clamp((theta - light.outerCutoff) / (light.innerCutoff - light.outerCutoff), 0.0, 1.0);

    vec3 ambientLightning = uSpotlight.ambient * vec3(texture(uMaterial.diffuse, texCoords));

    vec3 norm = normalize(normal);
    float diffuseStrength = max(dot(lightDir, norm), 0.0);
    vec3 diffuseLightning = diffuseStrength * uSpotlight.diffuse * vec3(texture(uMaterial.diffuse, texCoords));

    vec3 reflectDir = reflect(-lightDir, norm);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), uMaterial.shininess);
    vec3 specularLightning = specularStrength * uSpotlight.specular * vec3(texture(uMaterial.specular, texCoords));

    diffuseLightning *= intensity;
    specularLightning *= intensity;

    return attenuation * (ambientLightning + diffuseLightning + specularLightning);
}

vec3 calculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);

    vec3 ambientLightning = light.ambient * vec3(texture(uMaterial.diffuse, texCoords));

    vec3 norm = normalize(normal);
    float diffuseStrength = max(dot(lightDir, norm), 0.0f);
    vec3 diffuseLightning = diffuseStrength * light.diffuse * vec3(texture(uMaterial.diffuse, texCoords));

    vec3 reflectDir = reflect(-lightDir, norm);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), uMaterial.shininess);
    vec3 specularLightning = specularStrength * light.specular * vec3(texture(uMaterial.specular, texCoords));

    return ambientLightning + diffuseLightning + specularLightning;
}

void main()
{
    vec3 viewDir = normalize(uViewPosition - fragPos);

    vec3 resultColor = calculateSpotlight(uSpotlight, normal, viewDir);
    resultColor += calculateDirLight(uDirLight, normal, viewDir);

    FragColor = vec4(resultColor, 1.0);
}



