#pragma once
#include <iostream>
#include <vector>

class Matrix {
public:
	enum class RotationManner { ClockWise, AntiClockWise };
	Matrix();
	Matrix(int columns, int rows);
	Matrix(std::vector<float>& vector);
	Matrix(std::vector<std::vector<float>>& data);
	Matrix(const std::vector<std::vector<float>>& data);
	void SetValue(int column, int row, float value),
		GenerateRandom(), GenerateRandomInt(),
		Rotate(RotationManner), RotateClockWise(), RotateAntiClockWise(),
		Print(int columnStart, int rowStart, int columnEnd, int rowEnd),
		Print();
	float GetValue(int column, int row);
	int GetColumns(), GetRows();
	Matrix Multiply(Matrix otherMat);

private:
	void Initialize();
	std::vector<std::vector<float>> _mat;
	int columns, rows;
};

#define RotationManner Matrix::RotationManner