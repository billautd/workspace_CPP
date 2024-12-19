#version 330

in vec4 vColour;

out vec4 colour;

void main(){
	//colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	colour = vColour;
}