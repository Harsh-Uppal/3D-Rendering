#include "Main.h"

using namespace std;

GLfloat verts[] = {
// COORDINATES           COLORS
	 0, 0, 0,     1.0f, 0.0f, 0.0f,
	 0, 0, 0,     0.0f, 1.0f, 0.0f,
	 0, 0, 0,     0.0f, 0.0f, 1.0f,
	 0, 0, 0,     1.0f, 1.0f, 1.0f,
	 0, 0, 0,     1.0f, 0.0f, 0.0f,
	 0, 0, 0,     0.0f, 1.0f, 0.0f,
	 0, 0, 0,     0.0f, 0.0f, 1.0f,
	 0, 0, 0,     1.0f, 1.0f, 1.0f
};
GLuint indices[] = {
	0, 1, 1, 2, 2, 3, 3, 0,
	4, 5, 5, 6, 6, 7, 7, 4
};
short vaoAttribs[] = {
	3, 3
};

Matrix projectionMat(vector<vector<float>> { vector<float>{1, 0}, vector<float>{0, 1}, vector<float>{0, 0}});
const int MAX_FPS = 50;
const int SKIP_TICKS = 1000 / MAX_FPS;
const float PI = acos(0) * 2;

int main()
{
	Matrix(vector<float>{1, 1, 1}).Print();

	// Set up GLFW and Window
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(400, 400, "3D Rendering", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 400, 400);

	Shader shader("Shaders/default.vert", "Shaders/default.frag");
	Mesh2D mesh(generate_cube_verts(verts, 0, 0, 0), 48 * sizeof(float), indices, sizeof(indices), vaoAttribs, 2, GL_DYNAMIC_DRAW);

	GLuint scaleUni = glGetUniformLocation(shader.ID, "scale");
	shader.Activate();
	glUniform1f(scaleUni, 0);
	glLineWidth(5);

	int sleep_time = 0, deltaTime = 0, tickCount = GetTickCount64(), lastTickCount = 0, frameCount = 0;
	DWORD next_game_tick = tickCount;
	while (!glfwWindowShouldClose(window)) {
		//Update
		mesh.ChangeAllVertices(generate_cube_verts(verts, PI, 0, 0));

		//Display
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();
		mesh.BindVAO();
		glDrawElements(GL_LINES, sizeof(indices), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Calculate Tick Count and Sleep Time
		tickCount = GetTickCount64();
		deltaTime = tickCount - lastTickCount;
		lastTickCount = tickCount;
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - tickCount;
		if (sleep_time >= 0)
			Sleep(sleep_time);
		else
			cout << "Program lagging behind!" << endl;
		cout << "FPS: " << min(1000 / max(deltaTime, 1), MAX_FPS) << endl;

		frameCount++;
	}

	//End Program
	mesh.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

GLfloat* generate_cube_verts(GLfloat* verts, float rotX, float rotY, float rotZ) {
	short i = 0;
	for (float x = -.5f; x < .5f; x ++) {
		for (float y = -.5f; y < .5f; y ++) {
			for (float z = -.5f; z < .5f; z ++) {

				Matrix p = Matrix::Multiply(Matrix::Multiply(vector<float>{x, y, z}, rot_mat_x(rotX)), projectionMat);

				verts[i] = p.GetValue(0, 0);
				verts[i + 1] = p.GetValue(0, 1);
				verts[i + 2] = p.GetValue(0, 2);

				i += 6;
			}
		}
	}

	return verts;
}

Matrix rot_mat_x(float rot) {
	return Matrix(
		vector<vector<float>>{
		vector<float>{ 1, 0, 0}, 
		vector<float>{ 0, cos(rot), sin(rot)}, 
		vector<float>{ 0, -sin(rot), cos(rot)},
	});
}
Matrix rot_mat_y(float rot) {
	return Matrix(
		vector<vector<float>>{
		vector<float>{ cos(rot), 0, -sin(rot)},
		vector<float>{ 0, 1, 0},
		vector<float>{ sin(rot), 0, cos(rot)},
	});
}
Matrix rot_mat_z(float rot) {
	return Matrix(
		vector<vector<float>>{
		vector<float>{ cos(rot),sin(rot), 0},
		vector<float>{ -sin(rot), cos(rot), 0},
		vector<float>{ 0, 0, 1},
	});
}