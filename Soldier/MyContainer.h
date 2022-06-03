#pragma once

template <typename T>
class myContainer
{
public:
	myContainer() {};
	myContainer(const myContainer&);
	~myContainer();
	int size() const;
	void push_back(const T& ob);
	void pop_back();
	void erase(int delNumber);
	void clear();
	bool empty();
	const T& operator[] (int index) const;
	T& operator[] (int index);
	T* begin();
	T* end(); 
private:
	int size_arr = 0;
	T* arr = NULL;
};

template <class  T>
myContainer<T>::myContainer(const myContainer& other) {
	this->size = other.size;
	arr = new T[size];
	for (int i = 0; i < other.size; i++)
		this->arr[i] = other.arr[i];
}

template <class  T>
myContainer<T>::~myContainer() {
	delete[] arr;
}

template <class  T>
int myContainer<T>::size() const {
	return size_arr;
}

template <class  T>
void myContainer<T>::push_back(const T& ob) {
	T* newArray = new T[size() + 1];
	for (int i = 0; i < size_arr; i++)
		newArray[i] = arr[i];
	newArray[size_arr] = ob;
	size_arr++;
	delete[] arr;
	arr = newArray;
}

template <class  T>
void myContainer<T>::pop_back() {
	size_arr--;
	T* newArray = new T[size()];
	for (int i = 0; i < size_arr; i++)
		newArray[i] = arr[i];
	delete[] arr;
	arr = newArray;
}

template <class  T>
void myContainer<T>::erase(int delNumber) {
	T* newArray = new T[size() - 1];
	int i = 0;
	while (i < delNumber) {
		newArray[i] = arr[i];
		i++;
	}
	while (i < size_arr - 1) {
		newArray[i] = arr[i + 1];
		i++;
	}
	size_arr--;
	delete[] arr;
	arr = newArray;

}

template <class  T>
void myContainer<T>::clear() {
	size_arr = 0;
	delete[] arr;
	T* newArray = new T[size()];
	arr = newArray;
}

template <class  T>
bool myContainer<T>::empty() {
	return size_arr == 0;
}

template <class  T>
const T& myContainer<T>:: operator[] (int index) const {
	return arr[index];
}

template <class  T>
T& myContainer<T>:: operator[] (int index) {
	return arr[index];
}
