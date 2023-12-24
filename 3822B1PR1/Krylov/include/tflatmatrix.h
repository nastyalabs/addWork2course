#ifndef __TFLATMATRIX_H_
#define __TFLATMATRIX_H_

template<typename T>
class TFlatMatrix
{
private:
    size_t N;
    T* values;
public:
  explicit TFlatMatrix(size_t N)
    : N(N)
    , values(new T[N*N]())
  {}

  TFlatMatrix(const TFlatMatrix<T>& other)
    : N(other.N)
    , values(new T[N*N])
  {
      std::copy(other.values, other.values + N*N, values);
  }

  ~TFlatMatrix()
  {
      delete[] values;
  }

  size_t size() const
  {
      return N;
  }

  const T& at(size_t i, size_t j) const
  {
      return values[i * N + j];
  }

  T& at(size_t i, size_t j)
  {
      return values[i * N + j];
  }

  TFlatMatrix operator*(const TFlatMatrix& other) const
  {
      TFlatMatrix result(N);

      for (size_t i = 0; i < N; i++) {
          for (size_t j = 0; j < N; j++) {
              T acc{};
              for (size_t k = 0; k < N; k++) {
                  acc += at(i, k) * other.at(k, j);
              }
              result.at(i, j) = acc;
          }
      }

      return result;
  }

  TFlatMatrix& operator=(const TFlatMatrix& other) {
      if (this == &other)
          return *this;

      if (N != other.N)
      {
          delete[] values;
          values = new T[N*N];
      }

      N = other.N;
      std::copy(other.values, other.values + N*N, values);

      return *this;
  }

  friend std::ostream& operator<<(std::ostream& ostr, const TFlatMatrix& v)
  {
      for (size_t i = 0; i < v.N; i++) {
          for (size_t j = 0; j < v.N; j++)
          {
              ostr << v.at(i, j) << "   ";
          }
          ostr << std::endl;
      }
      return ostr;
  }
};

#endif // __TFLATMATRIX_H_
