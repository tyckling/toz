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

static const GLfloat gColorBufferData[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
};

GLuint vertexBuffer;
GLuint colorBuffer;
GLuint ProgramID;

GLuint LoadShaders(const char*, const char*);
int readFile(char**, const char*);

void setupTriangle()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(gColorBufferData), gColorBufferData, GL_STATIC_DRAW);

	ProgramID = LoadShaders("shaders/vertex.shader", "shaders/fragment.shader");
}

void draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(ProgramID);


	// Vertex buffer
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

	// Color buffer
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		1,
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

	char *vertexBuffer, *fragmentBuffer;

	if(!readFile(&vertexBuffer, vertexFilePath))
		return 0;
	if(!readFile(&fragmentBuffer, fragmentFilePath))
	{
		free(vertexBuffer);
		return 0;
	}
	
	GLint result = GL_FALSE;
	int InfoLogLength;

	printf("Comipling shader: %s\n", vertexFilePath);
	char const* vertexSourcePointer = vertexBuffer;
	glShaderSource(VertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength > 0)
	{
		char* vertexError = (char*)malloc(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, vertexError);
		printf("%s\n", vertexError);
		free(vertexError);
		
	}
	
	printf("Compiling shader: %s\n", fragmentFilePath);
	char const * fragmentSourcePointer = fragmentBuffer;
	glShaderSource(FragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength > 0)
	{
		char* fragmentError = (char*)malloc(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, fragmentError);
		printf("%s\n", fragmentError);
		free(fragmentError);
	}

	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength > 0)
	{
		char* programError = (char*)malloc(InfoLogLength + 1);
		glGetShaderInfoLog(ProgramID, InfoLogLength, NULL, programError);
		printf("%s\n", programError);
		free(programError);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	
	free(vertexBuffer);
	free(fragmentBuffer);

	return ProgramID;
}

int readFile(char** buffer, const char* filePath)
{
	int ret = 1;

	FILE* file = fopen(filePath, "r");
	if(file)
	{
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);

		*buffer = (char*)malloc(fsize + 1);
		printf("%li\n", sizeof(&buffer));

		fread(*buffer, 1, fsize, file);

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
