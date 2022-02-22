#include "Matrix.h";

//Matrix Constructors
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
Matrix::Matrix(const std::vector<std::vector<float>>& data)
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
//Fills the matrix with random values
void Matrix::GenerateRandom() {
	for (int c = 0; c < columns; c++)
		for (int r = 0; r < rows; r++)
			_mat[c][r] = std::rand() / 3276.7f;
}
//Fills the matrix with random integer values
void Matrix::GenerateRandomInt() {
	for (int c = 0; c < columns; c++)
		for (int r = 0; r < rows; r++)
			_mat[c][r] = std::rand() / 3277;
}
//Prints a section of the matrix
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
//Prints the whole matrix
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

//Matrix property geters
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

//Initializes the matrix
void Matrix::Initialize() {
	for (int i = 0; i < columns; i++)
	{
		_mat.push_back(*new std::vector<float>(rows));

		for (int g = 0; g < rows; g++)
			_mat[i].push_back(0);
	}
}

Matrix Matrix::Multiply(Matrix mat2) {

	mat2.RotateAntiClockWise();

	if (columns != mat2.GetColumns()) {
		throw new std::exception("Mat1's columns must equal Mat2's rows");
		return Matrix();
	}

	std::vector<std::vector<float>> newMat = std::vector<std::vector<float>>();

	float counter;
	for (int r = 0; r < mat2.GetRows(); r++) {
		newMat.push_back(std::vector<float>());
		for (int c = 0; c < rows; c++)
		{
			counter = 0;

			for (int i = 0; i < columns; i++)
				counter += _mat[i][c] * mat2.GetValue(i, mat2.GetRows() - r - 1);

			newMat[r].push_back(counter);
		}
	}

	columns = mat2.GetRows();

	return newMat;
}

//Rotates the the matrix
void Matrix::Rotate(RotationManner manner) {
	manner == Matrix::RotationManner::ClockWise ? RotateClockWise() : RotateAntiClockWise();
}
void Matrix::RotateClockWise() {
	std::vector<std::vector<float>> temp = _mat;
	_mat = std::vector<std::vector<float>>();
	
	for (int row = rows - 1; row >= 0; row--) {
		_mat.push_back(std::vector<float>());

		for (int column = 0; column < columns; column++)
			_mat[_mat.size() - 1].push_back(temp[column][row]);
	}

	int cols = columns;
	columns = rows;
	rows = cols;
}
void Matrix::RotateAntiClockWise() {
	std::vector<std::vector<float>> temp = _mat;
	_mat = std::vector<std::vector<float>>();

	for (int row = 0; row < rows; row++) {
		_mat.push_back(std::vector<float>());

		for (int column = columns - 1; column >= 0; column--)
			_mat[row].push_back(temp[column][row]);
	}

	int cols = columns;
	columns = rows;
	rows = cols;
}