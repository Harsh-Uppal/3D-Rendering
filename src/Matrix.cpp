#include "Matrix.h";

Matrix::Matrix() {
	this->_mat = std::vector<std::vector<float>>(0);
	columns = 0;
	rows = 0;
}
Matrix::Matrix(int columns, int rows)
{
	this->_mat = *new std::vector<std::vector<float>>(columns);
	this->columns = columns;
	this->rows = rows;

	Initialize();
}
Matrix::Matrix(std::vector<float>& data)
{
	if (data.size() == 0) {
		throw new std::exception("Invalid vector data passed to Matrix constructor");
		return;
	}

	this->_mat = std::vector<std::vector<float>>{ data };

	this->columns = 1;
	this->rows = data.size();
}
Matrix::Matrix(std::vector<std::vector<float>>& data)
{
	if (data.size() == 0) {
		throw new std::exception("Invalid vector data passed to Matrix constructor");
		return;
	}

	this->_mat = data;
	this->columns = data.size();
	this->rows = data[0].size();
}

void Matrix::SetValue(int column, int row, float num) {
	if (column < 0 || column >= columns || row < 0 || row >= rows) {
		std::cout << column << ":" << row;
		throw new std::exception("Invalid column or row index passed to Matrix::SetValue");
		return;
	}

	_mat[column][row] = num;
}
void Matrix::Print(int columnStart, int rowStart, int columnEnd, int rowEnd) {

	//Checking for errors
	if (columnStart > columns || columnEnd > columns || columnStart < 0 || columnEnd < 0
		|| rowStart > rows || rowEnd > rows || rowStart < 0 || rowEnd < 0) {
		throw new std::exception("Invalid section area passed to Matrix::Print");
		return;
	}

	std::cout << "Matrix " << columns << "*" << rows << std::endl;
	std::cout << "------------" << std::endl;

	for (int row = rowStart; row < rowEnd; row++)
	{
		for (int column = columnStart; column < columnEnd; column++)
			std::cout << _mat[column][row] << ' ';

		std::cout << std::endl;
	}

	std::cout << "------------" << std::endl;
}
void Matrix::Print() {
	std::cout << "Matrix " << columns << "*" << rows << std::endl;
	std::cout << "------------" << std::endl;
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
			std::cout << _mat[column][row] << ' ';

		std::cout << std::endl;
	}

	std::cout << "------------" << std::endl;
}

float Matrix::GetValue(int column, int row) {
	if (column < 0 || column >= columns || row < 0 || row >= rows) {
		throw new std::exception("Invalid column or row index passed to Matrix::GetValue");
		return NULL;
	}

	return _mat[column][row];
}
int Matrix::GetColumns() {
	return this->columns;
}
int Matrix::GetRows() {
	return this->rows;
}

void Matrix::Initialize() {
	for (int i = 0; i < columns; i++)
	{
		_mat.push_back(*new std::vector<float>(rows));

		for (int g = 0; g < rows; g++)
			_mat[i].push_back(0);
	}
}

Matrix Matrix::GenerateRandom(int columns, int rows) {
	Matrix newMat = Matrix(columns, rows);

	for (int c = 0; c < columns; c++)
		for (int r = 0; r < rows; r++)
			newMat.SetValue(c, r, (float)(std::rand() / 3276.7f));

	return newMat;
}
Matrix Matrix::Multiply(Matrix mat1, Matrix mat2) {

	mat2 = RotateAntiClockWise(mat2);

	if (mat1.GetColumns() != mat2.GetColumns()) {
		throw new std::exception("Mat1's columns must equal Mat2's rows");
		return Matrix();
	}

	Matrix newMat = Matrix(mat2.GetRows(), mat1.GetRows());
	float counter;

	for (int r = 0; r < newMat.GetRows(); r++)
		for (int c = 0; c < newMat.GetColumns(); c++)
		{
			counter = 0;

			for (int cOfMat1 = 0; cOfMat1 < mat1.GetColumns(); cOfMat1++)
				counter += mat1.GetValue(cOfMat1, r) *
				mat2.GetValue(cOfMat1, mat2.GetRows() - c - 1);

			newMat.SetValue(c, r, counter);
		}

	return newMat;
}
Matrix Matrix::Rotate(Matrix mat, RotationManner manner) {
	return manner == Matrix::RotationManner::ClockWise ? RotateClockWise(mat) : RotateAntiClockWise(mat);
}
Matrix Matrix::RotateClockWise(Matrix mat) {
	Matrix newMat = Matrix(mat.GetRows(), mat.GetColumns());

	for (int row = 0; row < mat.GetRows(); row++)
		for (int column = 0; column < mat.GetColumns(); column++)
			newMat.SetValue(row, column, mat.GetValue(column, mat.GetRows() - row - 1));

	return newMat;
}
Matrix Matrix::RotateAntiClockWise(Matrix mat) {
	Matrix newMat = Matrix(mat.GetRows(), mat.GetColumns());

	for (int row = 0; row < mat.GetRows(); row++)
		for (int column = 0; column < mat.GetColumns(); column++)
			newMat.SetValue(row, column, mat.GetValue(mat.GetColumns() - column - 1, row));

	return newMat;
}