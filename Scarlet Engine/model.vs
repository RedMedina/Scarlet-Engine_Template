#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

out vec2 UV;
out vec3 fragPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out vec3 LightDirection_tangentspace;
out vec3 outNormals;
out vec4 FragPosLightSpace;

// @uniform_name mvp
// @uniform_type mat4
uniform mat4 mvp;

// @uniform_name m
// @uniform_type mat4
uniform mat4 m;

// @uniform_name light_direction
// @uniform_type vec3
uniform vec3 light_direction;

// @uniform_name viewPos
// @uniform_type vec3
uniform vec3 viewPos;

// @uniform_name lightSpaceMatrix
// @uniform_type mat4
uniform mat4 lightSpaceMatrix;

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

void main()
{
    gl_Position =  mvp * vec4(position, 1.0f);
    fragPos = vec3(m * vec4(position, 1.0));
    UV = uvs;

    vec3 tangent1 = calculateTangent(position, position + vec3(1.0, 0.0, 0.0), position + vec3(0.0, 1.0, 0.0), UV, UV + vec2(1.0, 0.0), UV + vec2(0.0, 1.0));
    vec3 tangent2 = calculateTangent(position, position + vec3(0.0, 1.0, 0.0), position + vec3(0.0, 0.0, 1.0), UV, UV + vec2(0.0, 1.0), UV + vec2(0.0, 0.0));
    vec3 vTangent = normalize(tangent1 + tangent2);
    vec3 vBinormal = normalize(cross(normals, tangent1));

    mat3 normalMatrix = transpose(inverse(mat3(m)));
    vec3 T = normalize(mat3(m) * tangent1);
	vec3 B = normalize(mat3(m) * vBinormal);
	vec3 N = normalize(mat3(m) * normals);
	mat3 TBN = transpose(mat3(T, B, N));

    LightDirection_tangentspace = TBN * light_direction;
	TangentViewPos  = TBN * viewPos;
	TangentFragPos  = TBN * position;
    outNormals = normals;
    FragPosLightSpace = lightSpaceMatrix * vec4(position, 1.0);
} 