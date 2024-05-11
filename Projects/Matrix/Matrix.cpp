#include <algorithm>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() { matrix_.resize(N, std::vector<T>(M)); }

  Matrix(std::vector<std::vector<T> > other) { matrix_ = other; }

  Matrix(T elem);

  Matrix<N, M, T>& operator+=(const Matrix& other);

  Matrix<N, M, T>& operator-=(const Matrix& other);

  Matrix<N, M, T> operator+(const Matrix& other);

  Matrix<N, M, T> operator-(const Matrix& other);

  Matrix<N, M, T> operator*(const T& elem) const;

  template <size_t K>
  Matrix<N, K, T> operator*(const Matrix<M, K, T>& other) const;

  Matrix<M, N, T> Transposed();

  T& operator()(size_t ind_i, size_t ind_j) { return matrix_[ind_i][ind_j]; }

  const T& operator()(size_t ind_i, size_t ind_j) const {
    return matrix_[ind_i][ind_j];
  }

  bool operator==(const Matrix<N, M, T>& other);

 private:
  std::vector<std::vector<T> > matrix_;
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T elem) {
  matrix_.resize(N);
  for (size_t i = 0; i < N; i++) {
    matrix_[i].resize(M);
  }
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix_[i][j] = elem;
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(const Matrix& other) {
  Matrix copy = *this;
  copy += other;
  return copy;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(const Matrix& other) {
  Matrix copy = *this;
  copy -= other;
  return copy;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(const T& elem) const {
  Matrix result = *this;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      result(i, j) *= elem;
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
template <size_t K>
Matrix<N, K, T> Matrix<N, M, T>::operator*(const Matrix<M, K, T>& other) const {
  Matrix<N, K, T> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < K; j++) {
      for (size_t ii = 0; ii < M; ii++) {
        result(i, j) += matrix_[i][ii] * other(ii, j);
      }
    }
  }
  return result;
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  Matrix<M, N, T> transposed;
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      transposed(i, j) = matrix_[j][i];
    }
  }
  return transposed;
}

template <size_t N, size_t M, typename T>
bool Matrix<N, M, T>::operator==(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      if (matrix_[i][j] != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix() { matrix_.resize(N, std::vector<T>(N)); }

  Matrix(std::vector<std::vector<T> > other) { matrix_ = other; }

  Matrix(T elem);

  Matrix<N, N, T>& operator+=(const Matrix& other);

  Matrix<N, N, T>& operator-=(const Matrix& other);

  Matrix<N, N, T> operator+(const Matrix& other);

  Matrix<N, N, T> operator-(const Matrix& other);

  Matrix<N, N, T> operator*(const T& elem) const;

  template <size_t K>
  Matrix<N, K, T> operator*(const Matrix<N, K, T>& other) const;

  Matrix<N, N, T> Transposed();

  T Trace();

  T& operator()(size_t ind_i, size_t ind_j) { return matrix_[ind_i][ind_j]; }

  const T& operator()(size_t ind_i, size_t ind_j) const {
    return matrix_[ind_i][ind_j];
  }

  bool operator==(const Matrix<N, N, T>& other);

 private:
  std::vector<std::vector<T> > matrix_;
};

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(T elem) {
  matrix_.resize(N);
  for (size_t i = 0; i < N; i++) {
    matrix_[i].resize(N);
  }
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix_[i][j] = elem;
    }
  }
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator+=(const Matrix& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator-=(const Matrix& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator+(const Matrix& other) {
  Matrix copy = *this;
  copy += other;
  return copy;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator-(const Matrix& other) {
  Matrix copy = *this;
  copy -= other;
  return copy;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator*(const T& elem) const {
  Matrix result = *this;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      result(i, j) *= elem;
    }
  }
  return result;
}

template <size_t N, typename T>
template <size_t K>
Matrix<N, K, T> Matrix<N, N, T>::operator*(const Matrix<N, K, T>& other) const {
  Matrix<N, K, T> result;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < K; j++) {
      for (size_t ii = 0; ii < N; ii++) {
        result(i, j) += matrix_[i][ii] * other(ii, j);
      }
    }
  }
  return result;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::Transposed() {
  Matrix<N, N, T> transposed;
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      transposed(i, j) = matrix_[j][i];
    }
  }
  return transposed;
}

template <size_t N, typename T>
T Matrix<N, N, T>::Trace() {
  T trace = matrix_[0][0];
  for (size_t i = 1; i < N; i++) {
    trace += matrix_[i][i];
  }
  return trace;
}

template <size_t N, typename T>
bool Matrix<N, N, T>::operator==(const Matrix<N, N, T>& other) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (matrix_[i][j] != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}