#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

out vec2 UV;
out vec3 fragPos;
out vec3 outNormals;
out vec4 ClipSpace;
out vec3 ToCameraVector;
out vec3 LightDirection;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out vec3 LightDirection_tangentspace;
out vec4 FragPosLightSpace;

// @uniform_name mvp
// @uniform_type mat4
uniform mat4 mvp;

// @uniform_name m
// @uniform_type mat4
uniform mat4 m;
uniform mat4 p;
uniform mat4 v;

// @uniform_name light_direction
// @uniform_type vec3
uniform vec3 light_direction;

// @uniform_name viewPos
// @uniform_type vec3
uniform vec3 viewPos;

// @uniform_name lightSpaceMatrix
// @uniform_type mat4
uniform mat4 lightSpaceMatrix;

uniform float time; // Tiempo para animar las olas
float frequency = 9.0; // Frecuencia de las ondas
float amplitude = 0.05; // Amplitud de las ondas

vec3 calculateTangent(vec3 position1, vec3 position2, vec3 position3, vec2 uv1, vec2 uv2, vec2 uv3) {
    vec3 edge1 = position2 - position1;
    vec3 edge2 = position3 - position1;
    vec2 deltaUV1 = uv2 - uv1;
    vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    vec3 tangent;
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    return normalize(tangent);
}

vec3 CalculateCameraTarget(mat4 view) {
    // La dirección hacia adelante en el espacio de la cámara es el negativo del eje z
    vec3 cameraDirection = -vec3(view[2]);
    // La posición de la cámara está en la cuarta columna de la matriz de vista
    vec3 cameraPosition = vec3(view[3]);
    // El punto hacia el cual la cámara está mirando es la posición de la cámara más la dirección de la cámara
    return cameraPosition + cameraDirection;
}

mat4 CalculateViewMatrix(vec3 eye, vec3 target, vec3 up) {
    vec3 zaxis = normalize(eye - target);
    vec3 xaxis = normalize(cross(up, zaxis));
    vec3 yaxis = cross(zaxis, xaxis);

    mat4 viewMatrix = mat4(
        vec4(xaxis.x, yaxis.x, zaxis.x, 0.0),
        vec4(xaxis.y, yaxis.y, zaxis.y, 0.0),
        vec4(xaxis.z, yaxis.z, zaxis.z, 0.0),
        vec4(-dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1.0)
    );

    return viewMatrix;
}

void main()
{
    vec3 modifiedPosition = position;
    modifiedPosition.y += amplitude * sin(frequency * (modifiedPosition.x + time));

    gl_Position =  mvp * vec4(modifiedPosition, 1.0f);
    fragPos = vec3(m * vec4(modifiedPosition, 1.0));
    UV = uvs;

    vec3 tangent1 = calculateTangent(modifiedPosition, modifiedPosition + vec3(1.0, 0.0, 0.0), modifiedPosition + vec3(0.0, 1.0, 0.0), UV, UV + vec2(1.0, 0.0), UV + vec2(0.0, 1.0));
    vec3 tangent2 = calculateTangent(modifiedPosition, modifiedPosition + vec3(0.0, 1.0, 0.0), modifiedPosition + vec3(0.0, 0.0, 1.0), UV, UV + vec2(0.0, 1.0), UV + vec2(0.0, 0.0));
    vec3 vTangent = normalize(tangent1 + tangent2);
    vec3 vBinormal = normalize(cross(normals, tangent1));

    vec4 worldPos = m * vec4(position, 1.0f);
    mat4 view = v;
    vec3 CameraTarget = CalculateCameraTarget(v);
    vec3 cameraDirection = normalize(viewPos - CameraTarget);
    if (abs(dot(cameraDirection, vec3(0.0, 1.0, 0.0))) > 0.99) {
        // Si la cámara mira hacia arriba en el eje Y, ajusta la matriz de vista
        vec3 newCameraTarget = vec3(CameraTarget.x, CameraTarget.y, viewPos.z);
        view = CalculateViewMatrix(viewPos, newCameraTarget, vec3(v[1]));
    }
    ClipSpace = p * view * worldPos;

    ToCameraVector = (viewPos - worldPos.xyz);
    LightDirection = (worldPos.xyz - light_direction);

    mat3 normalMatrix = transpose(inverse(mat3(m)));
    vec3 T = normalize(normalMatrix * vTangent);
    vec3 N = normalize(normalMatrix * normals);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N));   

    LightDirection_tangentspace = TBN * light_direction;
	TangentViewPos  = TBN * viewPos;
	TangentFragPos  = TBN * position;
    outNormals = normals;
    FragPosLightSpace = lightSpaceMatrix * vec4(position, 1.0);
} 