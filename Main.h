#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <vector>

#include "Matrix.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

GLfloat* generate_cube_verts(GLfloat* verts, float rotX, float rotY, float rotZ);

Matrix rot_mat_x(float rotation);
Matrix rot_mat_y(float rotation);
Matrix rot_mat_z(float rotation);