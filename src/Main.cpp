#include "Main.h"

using namespace std;

GLfloat cubeVerts[48];
GLfloat headerVerts[] = {
	-.7, .5, 0, 0, 0,
	 .7, .5, 0, 1, 0,
	 .7,  .8, 0, 1, 1,
	-.7,  .8, 0, 0, 1
};
GLuint headerIndices[] = { 
	0, 1, 2, 0, 2, 3
};
GLuint cubeIndices[] = {
	0, 1, 1, 3, 0, 2, 2, 3,
	4, 5, 5, 7, 4, 6, 6, 7,
	0, 4, 1, 5, 2, 6, 3, 7
};

vector<vector<float>> projMat = { vector<float>{1, 0}, vector<float>{0, 1}, vector<float>{0, 0} };
const Matrix projectionMat(projMat);
const int MAX_FPS = 50;
const int SKIP_TICKS = 1000 / MAX_FPS;
const float PI = acos(0) * 2;

int main()
{
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
	
	update_cube_verts(0, 0, 0);

	Shader meshShader("Shaders/default.vert", "Shaders/default.frag");
	Shader texShader("Shaders/texture.vert", "Shaders/texture.frag");
	
	Mesh2D header(headerVerts, sizeof(headerVerts), headerIndices, sizeof(headerIndices), new short[] {3, 2}, 2, GL_STATIC_DRAW);
	Mesh2D cube(cubeVerts, sizeof(cubeVerts), cubeIndices, sizeof(cubeIndices), new short[] {3}, 1, GL_DYNAMIC_DRAW);

	GLuint scaleUni = glGetUniformLocation(meshShader.ID, "scale");
	meshShader.Activate();
	glUniform1f(scaleUni, -.5f);

	Texture headingTex("Assets/Heading.png", GL_TEXTURE_2D, GL_TEXTURE0);
	headingTex.texUnit(texShader, "tex0", 0);

	glLineWidth(50);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DWORD tickCount = GetTickCount64();
	DWORD next_game_tick = tickCount;
	int sleep_time = 0, deltaTime = 0, lastTickCount = 0, frameCount = 0;
	float rot = 0;
	while (!glfwWindowShouldClose(window)) {
		//Update
		rot = sin(tickCount / 1000.0f) * PI;
		update_cube_verts(rot, rot, rot);
		cube.ChangeAllVertices(cubeVerts);
		
		//Display
		glClearColor(.1, .3, .4, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		meshShader.Activate();
		cube.Draw(GL_LINES);
		texShader.Activate();
		headingTex.Bind();
		header.Draw(GL_TRIANGLES);

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

		frameCount++;
	}

	//End Program
	cube.Delete();
	meshShader.Delete();
	texShader.Delete();
	headingTex.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void update_cube_verts(float rotX, float rotY, float rotZ) {
	Matrix p;
	vector<float> pos;
	short i = 0;

	for (float x = -.5f; x < 1; x++) {
		for (float y = -.5f; y < 1; y++) {
			for (float z = -.5f; z < 1; z++) {
				pos = { x, y, z };
				p = MatMul(projectionMat, MatMul(rot_mat(rotX, rotY, rotZ), pos));

				cubeVerts[i] = p.GetValue(0, 0);
				cubeVerts[i + 1] = p.GetValue(0, 1);
				cubeVerts[i + 2] = 0;

				i += 3;
			}
		}
	}
}

Matrix rot_mat(float rx, float ry, float rz) {
	return MatMul(rot_x_mat(rx), MatMul(rot_y_mat(ry), rot_z_mat(rz)));
}

Matrix rot_x_mat(float rot) {
	vector<vector<float>> mat = {
		vector<float>{ 1, 0, 0},
		vector<float>{ 0, cos(rot), sin(rot)},
		vector<float>{ 0, -sin(rot), cos(rot)} };
	
	return Matrix(mat);
}
Matrix rot_y_mat(float rot) {
	vector<vector<float>> mat = {
		vector<float>{ cos(rot), 0, -sin(rot)},
		vector<float>{ 0, 1, 0},
		vector<float>{ sin(rot), 0, cos(rot)} };
	return Matrix(mat);
}
Matrix rot_z_mat(float rot) {
	vector<vector<float>> mat = {
		vector<float>{ cos(rot),sin(rot), 0},
		vector<float>{ -sin(rot), cos(rot), 0},
		vector<float>{ 0, 0, 1}};
	return Matrix(mat);
}