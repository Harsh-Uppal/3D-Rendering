#include "Mesh.h"

Mesh2D::Mesh2D(GLfloat* verts, GLuint vertCnt, GLuint* indices, GLuint indCnt, short* vaoAttribLengths, size_t attribCount, GLenum vboUsage) {
	vao.Bind();
	vbo = VBO(verts, vertCnt * sizeof(float), vboUsage);
	EBO _ebo(indices, indCnt);

	int total = 0;
	for (int i = 0; i < attribCount; i++)
		total += vaoAttribLengths[i];

	int cTotal = 0;
	for (int i = 0; i < attribCount; i++) {
		vao.LinkAttrib(vbo, i, vaoAttribLengths[i], GL_FLOAT, total * sizeof(float), (void*)(cTotal * sizeof(float)));
		cTotal += vaoAttribLengths[i];
	}

	vao.Unbind();
	vbo.Unbind();
	_ebo.Unbind();

	vertCount = vertCnt;
	indCount = indCnt;
}

void Mesh2D::ChangeVertices(int start, int size, void* vertices) {
	vbo.ChangeVertices(start, size, vertices);
}
void Mesh2D::ChangeAllVertices(void* vertices){
	vbo.ChangeVertices(0, vertCount, vertices);
}
void Mesh2D::BindVAO() {
	vao.Bind();
}
void Mesh2D::Draw(GLenum type) {
	vao.Bind();
	glDrawElements(type, indCount, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
void Mesh2D::Delete() {
	vao.Delete();
}