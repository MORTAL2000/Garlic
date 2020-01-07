#version 460 core

layout(location = 0) in vec3 Position3D;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec3 Normal; //TODO: Remove now that we have shader reflection

layout(std140, binding = 1) uniform CameraMatrices {
	mat4 view;
	mat4 projection;
};

layout(std140, binding = 4) uniform modelBuffer {
	mat4 model;
	mat4 normalMatrix;
};

out vec2 vertTexCoord;

void main(){
	const vec4 pos4D = vec4(Position3D, 1.0f);

	gl_Position = projection * view * model * pos4D;
  
	vertTexCoord = TexCoord;
};
