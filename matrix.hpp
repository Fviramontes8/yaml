/**
 * @file matrix.hpp
 * @brief Contains a template matrix class to support operations of a 2-D 
 *  matrix
 * @author Francisco Viramontes
 */
#include <cassert>	// assert
#include <concepts> // std::integral, std::floating_point
#include <ostream>	// std::ostream
#include <vector>	// std::vector

/**
 * @brief Concept that only allows Number to be a type of int or float
 */
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

/**
 * @brief A 2-D matrix class for linear algebra operatations
 *
 * @see Number
 *
 * @tparam T A number that can be a type of integer (int, unsigned, long) or 
 *		a floating point number (float/double). Refer to the course file on
 *		more information on the user-defined Number concept
 */
template <Number N>
class Matrix {
	private:
		/**
		 * Contains the data of the matrix
		 */
		std::vector<std::vector<N>> _data;
		/**
		 * Represents the rows of the matrix
		 */
		std::size_t _rows;
		/**
		 * Represents the columns of the matrix
		 */
		std::size_t _cols;

	public:
		/**
		 * @brief Parameterized default constructor, will resize _data
		 * 	attribute with the appropriate rows and columns
		 *
		 * @param rows Number of rows
		 * @param cols Number of columns
		 */
		Matrix(std::size_t rows, std::size_t cols) :
				_rows{rows}, _cols{cols} {
			_data.resize(_rows, std::vector<N>(_cols));
		}

		/**
		 * @brief Parameterized default constructor, will resize _data
		 * 	attribute with the appropriate rows and columns then set them
		 * 	all to the value specified by parameter init_val
		 *
		 * @param rows Number of rows
		 * @param cols Number of columns
		 * @param init_val Value to initialize the matrix
		 */
		Matrix(std::size_t rows, std::size_t cols, N init_val) :
				_rows{rows}, _cols{cols} {
			_data.resize(_rows, std::vector<N>(_cols));

			for (auto &i: _data) {
				for (auto &j: i) {
					j = init_val;
				}
			}
		}

		/**
		 * @brief Copy constructor for Matrix
		 *
		 * @param mat Source Matrix that will be copied
		 * 	to the newly created instance
		 */
		Matrix(const Matrix& mat): _data{mat._data}, _rows{mat._rows}, 
			_cols{mat._cols} {}

		/**
		 * @brief Move constructor for Matrix.
		 *
		 * 	After move, using mat will mostly likely lead to undefined
		 * 	behavior.
		 *
		 * @param mat Matrix to be moved to current instance.
		 */
		Matrix(Matrix&& mat): _data{std::move(mat._data)},
			_rows{std::move(mat._rows)}, _cols{std::move(mat._cols)} {}

		/**
		 * @brief Getter for _rows attribute
		 *
		 * @return Number of rows of Matrix instance
		 */
		std::size_t rows() const {
			return _rows;
		}

		/**
		 * @brief Getter for _cols attribute
		 *
		 * @return Number of columns of Matrix instance
		 */
		std::size_t cols() const {
			return _cols;
		}

		/**
		 * @brief Alternative getter for _cols attribute
		 * @see cols()
		 * @return Number of columns of Matrix instance
		 */
		std::size_t columns() const {
			return cols();
		}

		/**
		 * @brief Creates a new Matrix and transposes the current instance
		 *  into the new one
		 *
		 * @return Transposed Matrix
		 */
		Matrix transpose() {
			Matrix t(cols(), rows());
			for (std::size_t i=0; i<rows(); ++i) {
				for (std::size_t j=0; j<cols(); ++j) {
					t[j][i] = _data[i][j];
				}
			}
			return t;
		}

		/**
		 * @brief Alternative methods for transpose
		 * @see transpose()
		 *
		 * @return Transposed Matrix
		 */
		Matrix T() {
			return transpose();
		}

		/**
		 * @brief Element-wise addition of two matrices
		 * @see operator+()
		 *
		 * @param m Second Matrix to be added (the first is the current
		 *  instance)
		 * @return Resulting Matrix which is the element-wise sum of the
		 *  current instance and m
		 */
		Matrix seq_add(const Matrix& m) {
			assert(rows() == m.rows());
			assert(cols() == m.cols());
			Matrix result(rows(), cols());
			for (std::size_t i=0, j=0, k=0; i<rows(); ++i, ++j, ++k) {
				for (std::size_t x=0, y=0, z=0; x<cols(); ++x, ++y, ++z) {
					result[k][z] = _data[i][x] + m[j][y];
				}
			}
			return result;
		}

		/**
		 * @brief Operator overload for = that does element-wise addition 
		 *  of two matrices
		 * @see add()
		 *
		 * @param m Second Matrix to be added (the first is the current
		 *  instance)
		 * @return Resulting Matrix which is the element-wise sum of the
		 *  current instance and m
		 */
		Matrix operator+(const Matrix& m) {
			return seq_add(m);
		}

		/**
		 * @brief Operator[] overload, should be used with an additional pair 
		 * of [] to access column of a matrix. Will abort program if the index
		 * is greater than the rows
		 *
		 * @param idx Index to access the rows of the matrix
		 * @return A vector reference, offset by the row,
		 *  that gives access to the columns of the Matrix class instance
		 */
		std::vector<N>& operator[](std::size_t idx) {
			assert(idx<_rows);
			return _data[idx];
		}

		/**
		 * @brief const version of [] operator
		 * @see operator[]()
		 *
		 * @param idx Index to access the rows of the matrix
		 * @return A const vector reference, offset by the row,
		 *  that gives access to the columns of the Matrix class instance
		 */
		const std::vector<N>& operator[](std::size_t idx) const {
			assert(idx<_rows);
			return _data[idx];
		}

		/**
		 * @brief Assignment operator for the Matrix class
		 *
		 * @param m Matrix to be assigned to the current instance
		 * @return The current instance assigned with the same attributes as m
		 */
		Matrix& operator=(const Matrix& m) {
			if (this == &m) {
				return *this;
			}
			_data = m._data;
			_rows = m._rows;
			_cols = m._cols;

			return *this;
		}

		/**
		 * @brief Comparisson == operator overload
		 *
		 * @param rhs Matrix to compare with the current instance
		 * @return A boolean indicating if the matrices are equal (true) or if
		 *  they are not (false)
		 */
		bool operator==(const Matrix& rhs) {
			assert(rows() == rhs.rows());
			assert(cols() == rhs.cols());
			for (std::size_t i=0, j=0; i<rows(); ++i, ++j) {
				for (std::size_t x=0, y=0; x<cols(); ++x, ++y) {
					if (_data[i][x] != rhs[j][y]) {
						return false;
					}
				}
			}
			return true;
		}

		/**
		 * @brief Comparisson != operator overload
		 * @see operator==()
		 *
		 * @param rhs Matrix to compare with the current instance
		 * @return A boolean indicating if the matrices are not equal (true)
		 *  or if they are not (false)
		 */
		bool operator!=(const Matrix& rhs) {
			return !(*this == rhs);
		}


		/**
		 * @brief Overloads the << operator for printing the contents of the
		 * matrix
		 *
		 * @param out The output stream (usually std::cout)
		 * @param m The matrix to print the contents of
		 * @return The output stream with the contents of the matrix
		 */
		template <Number X>
		friend std::ostream& operator<<(std::ostream& out, const Matrix<X>& m);
};

template <Number X>
std::ostream& operator<<(std::ostream& out, Matrix<X> const& m) {
	for (const auto &i: m._data) {
		for (const auto &j: i) {
			out << j << ' ';
		}
		out << '\n';
	}
	return out;
}

