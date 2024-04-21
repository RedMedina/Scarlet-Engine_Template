#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

out float Height;
out vec3 Position;
out vec3 fragPos;
out vec2 UVs;
out vec3 outNormals;

/*Light*/
out vec4 FragPosLightSpace;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out vec3 LightDirection_tangentspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;
uniform mat4 lightSpaceMatrix;
uniform vec3 light_direction;

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
    Height = aPos.y;
    Position = (view * model * vec4(aPos, 1.0)).xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 tangent1 = calculateTangent(aPos, aPos + vec3(1.0, 0.0, 0.0), aPos + vec3(0.0, 1.0, 0.0), uvs, uvs + vec2(1.0, 0.0), uvs + vec2(0.0, 1.0));
    vec3 tangent2 = calculateTangent(aPos, aPos + vec3(0.0, 1.0, 0.0), aPos + vec3(0.0, 0.0, 1.0), uvs, uvs + vec2(0.0, 1.0), uvs + vec2(0.0, 0.0));
    vec3 vTangent = normalize(tangent1 + tangent2);
    vec3 vBinormal = normalize(cross(normals, tangent1));

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(mat3(model) * tangent1);
	vec3 B = normalize(mat3(model) * vBinormal);
	vec3 N = normalize(mat3(model) * normals);
    mat3 TBN = transpose(mat3(T, B, N));

    LightDirection_tangentspace = TBN * light_direction;
    TangentViewPos = TBN * viewPos;
	TangentFragPos = TBN * aPos;

    FragPosLightSpace = lightSpaceMatrix * vec4(aPos, 1.0);
    outNormals = normals;
    UVs = uvs;
}