#version 330

layout (location = 0) in vec3 pos;

out vec4 vColour;

uniform mat4 model;

void main(){
	gl_Position = model * vec4(pos, 1.0f);
	vColour = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}