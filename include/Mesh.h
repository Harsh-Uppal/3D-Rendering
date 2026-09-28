#pragma once
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh2D {
public:
	Mesh2D(
		GLfloat* verts,
		GLuint vertexCount,
		GLuint* indices,
		GLuint indexCount,
		short* vaoAttribLengths,
		size_t attribCount,
		GLenum vboUsage);
	void ChangeVertices(int start, int size, void* vertices), ChangeAllVertices(void* vertices),
		BindVAO(),
		Draw(GLenum type),
		Delete();

private:
	int vertCount, indCount;
	VAO vao;
	VBO vbo;
};