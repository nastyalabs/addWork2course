#pragma once
#include <iostream>

#define MAX_VECTOR_SIZE 100000
#define EXP_COEF 1.5

template <class T>
class TVector {
private:
	T* data;
	size_t size;
	size_t capacity;

	void resize();
	void swap(T& firstEl, T& secondEl);

public:
	TVector(int arrSize = 2);
	TVector(const T* values, int arrSize);
	TVector(const TVector<T>& obj);
	TVector(TVector<T>&& obj) noexcept;

	~TVector() { delete[] data; }

	void pop_back();
	void push_back(const T& elem);

	T& operator[](int index);
	const T& operator[](int index) const;

	T& at(int index);
	const T& at(int index) const;

	bool isEmpty() const noexcept;

	size_t getSize() const noexcept { return size; }
	size_t getCapacity() const noexcept { return capacity; }

	bool operator==(const TVector<T>& obj) const noexcept;
	bool operator!=(const TVector<T>& obj) const noexcept;

	TVector<T>& operator=(const TVector<T>& obj);
};

template <class T>
void TVector<T>::resize() {
	T* tmp = new T[capacity];

	for (size_t i = 0; i < size; i++) { tmp[i] = data[i]; }

	delete[] data;

	data = new T[(size_t)(capacity * EXP_COEF) + 1];
	for (size_t i = 0; i < size; i++) { data[i] = tmp[i]; }

	capacity = (size_t)(capacity * EXP_COEF) + 1;
}

template <class T>
void TVector<T>::swap(T& firstEl, T& secondEl) {
	T temp = std::move(firstEl);
	firstEl = std::move(secondEl);
	secondEl = std::move(temp);
}

template <class T>
TVector<T>::TVector(int arrSize) {
	if (arrSize < 1 || arrSize > MAX_VECTOR_SIZE) throw std::length_error("Invalid vector size!");

	size = arrSize;
	capacity = (size_t)(size * EXP_COEF) + 1;
	data = new T[capacity];
}

template <class T>
TVector<T>::TVector(const T* values, int arrSize) {
	if (arrSize < 1 || arrSize > MAX_VECTOR_SIZE) throw std::length_error("Invalid vector size!");

	size = arrSize;
	capacity = (size_t)(size * EXP_COEF) + 1;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++) {
		data[i] = values[i];
	}
}

template <class T>
TVector<T>::TVector(const TVector<T>& obj) {
	this->size = obj.size;
	this->capacity = obj.capacity;
	this->data = new T[capacity];

	for (size_t i = 0; i < size; i++) {
		this->data[i] = obj.data[i];
	}
}

template <class T>
TVector<T>::TVector(TVector<T>&& obj) noexcept {
	this->size = obj.size;
	this->capacity = obj.capacity;
	this->data = obj.data;
	obj.data = nullptr;
}

template <class T>
void TVector<T>::pop_back() {
	if (size < 1) throw std::length_error("Vector is empty!");
	--size;
}

template <class T>
void TVector<T>::push_back(const T& elem) {
	if (size + 1 == capacity) { resize(); }
	data[size - 1] = elem;
	++size;
}

template <class T>
T& TVector<T>::operator[](int index) {
	return data[index];
}

template <class T>
const T& TVector<T>::operator[](int index) const {
	return data[index];
}

template <class T>
T& TVector<T>::at(int index) {
	if (index < 0 || index >= size) throw std::out_of_range("Out of range!");
	return data[index];
}

template <class T>
const T& TVector<T>::at(int index) const {
	if (index < 0 || index >= size) throw std::out_of_range("Out of range!");
	return data[index];
}

template <class T>
bool TVector<T>::isEmpty() const noexcept {
	return (size == 0);
}

template <class T>
bool TVector<T>::operator==(const TVector<T>& obj) const noexcept {
	if (this->size != obj.size) return false;

	for (size_t i = 0; i < size; i++) {
		if (this->data[i] != obj.data[i]) return false;
	}

	return true;
}

template <class T>
bool TVector<T>::operator!=(const TVector<T>& obj) const noexcept {
	if (this->size != obj.size) return true;

	for (size_t i = 0; i < size; i++) {
		if (this->data[i] != obj.data[i]) return true;
	}

	return false;
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& obj) {
	if (*this != obj) {
		if (this->capacity != obj.capacity) {
			this->capacity = obj.capacity;
			delete[] this->data;
			this->data = new T[capacity];
		}
		this->size = obj.size;
		for (size_t i = 0; i < obj.size; i++) {
			this->data[i] = obj.data[i];
		}
	}
	return *this;
}