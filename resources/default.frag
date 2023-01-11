#version 330 core
out vec4 FragColor;
//uniform vec4 u_color;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 worldPos;

uniform sampler2D diffuse0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

// Implementing lights

vec4 pointLight(){

    vec3 lightVector = lightPos - worldPos; // distance frrom the light source
    float dist = length(lightVector);
    float a = 0.5;
    float b = 0.1;
    // Calulating Inensity (using a,b just to modify lights more)
    float intensity = 1.0f / (a*dist*dist + b*dist + 1.0f);
    // amount of lights for the backfaces
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVector);

    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - worldPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmnt = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmnt * specularLight;

    return (texture(diffuse0, texCoord)*lightColor*(diffuse*intensity + ambient + specular*intensity));
}

vec4 directionalLight(){
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - worldPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmnt = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmnt * specularLight;

    return (texture(diffuse0, texCoord)*lightColor*(diffuse + ambient + specular));

}

vec4 spotLight()
{
    // Area of light diffusion
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - worldPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - worldPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient));
}

void main()
{
    // pointLight, directionalLight or, spotLight
    FragColor = spotLight();
}