#include"VBO.h"
#include <iostream>

VBO::VBO() {
	ID = 0;
	size = 0;
}
VBO::VBO(GLfloat* vertices, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	this->size = size;
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::ChangeVertices(int start, int size, void* vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, start * sizeof(float), size * sizeof(float), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::ChangeAllVertices(void* vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}