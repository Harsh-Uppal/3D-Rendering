#pragma once
#include<glad/glad.h>

//Vertex Buffer Object
class VBO
{
public:
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size, GLenum usage);

	void ChangeVertices(int start, int size, void* vertices),
		ChangeAllVertices(void* vertices),
		Bind(), Unbind(), Delete();

private:
	GLuint ID;
	int size;
};