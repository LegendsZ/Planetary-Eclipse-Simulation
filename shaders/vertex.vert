#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertColour;
/*layout(location = 0) */out vec4 fragColour;
void main()
{
    fragColour = vec4(vertColour, 1.0);
	gl_Position = vec4(vertPos, 1.0);
}

//https://www.youtube.com/watch?v=2uVEUXsFM8c&list=PLalVdRk2RC6ofNC8_LvX-_RF3-HHJ5VNM&index=4
//5:25