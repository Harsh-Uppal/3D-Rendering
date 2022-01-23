#pragma once
#include <iostream>
#include <vector>

class Matrix {
public:
	enum class RotationManner { ClockWise, AntiClockWise };
	Matrix();
	Matrix(int columns, int rows);
	Matrix(std::vector<float> vector);
	Matrix(std::vector<std::vector<float>> data);
	void SetValue(int column, int row, float value),
		Print(int columnStart, int rowStart, int columnEnd, int rowEnd),
		Print();
	float GetValue(int column, int row);
	int GetColumns(), GetRows();
	static Matrix Multiply(Matrix, Matrix), GenerateRandom(int columns, int rows),
	Rotate(Matrix, RotationManner), RotateClockWise(Matrix), RotateAntiClockWise(Matrix);

private:
	void Initialize();
	std::vector<std::vector<float>> _mat;
	int columns, rows;
};