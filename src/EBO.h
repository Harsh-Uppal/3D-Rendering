#pragma once
#include<glad/glad.h>

//Element Buffer Object
class EBO
{
	GLuint ID;
public:
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind(), Unbind(), Delete();
};