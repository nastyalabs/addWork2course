#include <iostream>

#define MAX_DIM 1000

template <class T>
class TFlatMatrix {
private:
	T* data;
	size_t n; //dimension

public:
	TFlatMatrix(int dim = 2);
	TFlatMatrix(const TFlatMatrix<T>& obj);
	TFlatMatrix(TFlatMatrix<T>&& obj) noexcept;

	~TFlatMatrix() { delete[] data; }
	
	//utilities
	size_t GetDim() const noexcept { return n; }

	T& operator()(int i, int j);
	const T& operator()(int i, int j) const;

	TFlatMatrix& operator=(const TFlatMatrix<T>& obj);

	bool operator==(const TFlatMatrix<T>& obj) const noexcept;
	bool operator!=(const TFlatMatrix<T>& obj) const noexcept;

	//multiply
	TFlatMatrix<T> operator*(const T& obj);
	TFlatMatrix<T> operator*(const TFlatMatrix<T>& obj);
};

template <class T>
std::ostream& operator<<(std::ostream& ostr, const TFlatMatrix<T>& obj) {
	for (size_t i = 0; i < obj.GetDim(); i++) {
		for (size_t j = 0; j < obj.GetDim(); j++) {
			ostr << obj(i, j) << " ";
		}
		ostr << "\n";
	}
	return ostr;
}

template <class T>
TFlatMatrix<T>::TFlatMatrix(int dim) {
	if (dim < 1 || dim > MAX_DIM) throw std::length_error("Invalid dimension!");
	n = dim;
	data = new T[n * n];
}

template <class T>
TFlatMatrix<T>::TFlatMatrix(const TFlatMatrix<T>& obj) {
	this->n = obj.n;
	this->data = new T[n * n];
	for (size_t i = 0; i < n * n; i++) {
		this->data[i] = obj.data[i];
	}
}

template <class T>
TFlatMatrix<T>::TFlatMatrix(TFlatMatrix<T>&& obj) noexcept {
	this->n = obj.n;
	this->data = obj.data;
	obj.data = nullptr;
}

template <class T>
T& TFlatMatrix<T>::operator()(int i, int j) {
	return data[i * n + j];
}

template <class T>
const T& TFlatMatrix<T>::operator()(int i, int j) const {
	return data[i * n + j];
}

template <class T>
TFlatMatrix<T>& TFlatMatrix<T>::operator=(const TFlatMatrix<T>& obj) {
	if (obj != *this) {
		this->n = obj.n;
		delete[] this->data;
		this->data = new T[n * n];
		for (size_t i = 0; i < n * n; i++) {
			this->data[i] = obj.data[i];
		}
	}
	return *this;
}

template <class T>
bool TFlatMatrix<T>::operator==(const TFlatMatrix<T>& obj) const noexcept {
	if (this->n != obj.n) return false;

	for (size_t i = 0; i < n * n; i++) {
		if (this->data[i] != obj.data[i]) return false;
	}

	return true;
}

template <class T>
bool TFlatMatrix<T>::operator!=(const TFlatMatrix<T>& obj) const noexcept {
	if (this->n != obj.n) return true;

	for (size_t i = 0; i < n * n; i++) {
		if (this->data[i] != obj.data[i]) return true;
	}

	return false;
}

template <class T>
TFlatMatrix<T> TFlatMatrix<T>::operator*(const T& obj) {
	TFlatMatrix<T> res(*this);
	for (size_t i = 0; i < n * n; i++) {
		res.data[i] *= obj;
	}
	return res;
}

template <class T>
TFlatMatrix<T> TFlatMatrix<T>::operator*(const TFlatMatrix<T>& obj) {
	if (obj.n != this->n) throw std::length_error("Dimensions are not equal!");
	TFlatMatrix<T> res(n);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			T sum = 0;
			for (size_t k = 0; k < n; k++) {
				sum += this->data[i * n + k] * obj.data[k * n + j];
			}
			res.data[i * n + j] = sum;
		}
	}
	return res;
}