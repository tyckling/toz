#include <stdio.h>
#include <stdlib.h>

#include "gl.h"
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"


static const GLfloat gVertexBufferData[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

GLuint vertexBuffer;

GLuint LoadShaders(const char*, const char*);
int readFile(char*, int size, const char*);

void setupTriangle()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);

	LoadShaders("shaders/vertex.shader", "shaders/fragment.shader");
}

void draw()
{

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	char vertexBuffer[255], fragmentBuffer[255];

	if(!readFile(vertexBuffer, sizeof(vertexBuffer), vertexFilePath))
		return 0;
	if(!readFile(fragmentBuffer, sizeof(fragmentBuffer), fragmentFilePath))
		return 0;
	
	printf("%s", vertexBuffer);
	printf("%s", fragmentBuffer);
	
	return 0;
}

int readFile(char* buffer, int size, const char* filePath)
{
	int ret = 1;

	FILE* file = fopen(filePath, "r");
	if(file)
	{
		long fsize = fread(buffer, 1, size, file);

		if(ferror(file))
		{
			printf("Error reading file: %s\n", filePath);
			ret = -1;
		}

		fclose(file);

		buffer[fsize] = 0;
	}

	return ret;
}
