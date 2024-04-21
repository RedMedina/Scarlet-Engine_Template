#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 uvs;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in ivec4 boneIds; 
layout (location = 6) in vec4 weights;

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

// @uniform_name v
// @uniform_type mat4
uniform mat4 v;

// @uniform_name p
// @uniform_type mat4
uniform mat4 p;

// @uniform_name light_direction
// @uniform_type vec3
uniform vec3 light_direction;

// @uniform_name viewPos
// @uniform_type vec3
uniform vec3 viewPos;

// @uniform_name lightSpaceMatrix
// @uniform_type mat4
uniform mat4 lightSpaceMatrix;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[100]; //MAX_BONES

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(position, 1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(position, 1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * normals;
    }

    mat4 viewModel = v * m;
    gl_Position =  p * viewModel * totalPosition;
    //gl_Position =  mvp * vec4(position, 1.0f);
    fragPos = vec3(m * vec4(position, 1.0));
    UV = uvs;

    vec3 vTangent = normalize(tangent);
    vec3 vBinormal = normalize(bitangent);

    mat3 normalMatrix = transpose(inverse(mat3(m)));
    vec3 T = normalize(mat3(m) * tangent);
	vec3 B = normalize(mat3(m) * vBinormal);
	vec3 N = normalize(mat3(m) * normals);
	mat3 TBN = transpose(mat3(T, B, N));

    LightDirection_tangentspace = TBN * light_direction;
	TangentViewPos  = TBN * viewPos;
	TangentFragPos  = TBN * position;
    outNormals = normals;
    FragPosLightSpace = lightSpaceMatrix * vec4(position, 1.0);
} 