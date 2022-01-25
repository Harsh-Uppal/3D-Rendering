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

void update_cube_verts(float rotX, float rotY, float rotZ);

Matrix rot_mat(float rotX, float rotY, float rotZ);

Matrix rot_x_mat(float rotation);
Matrix rot_y_mat(float rotation);
Matrix rot_z_mat(float rotation);