#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<iostream>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate(), Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};