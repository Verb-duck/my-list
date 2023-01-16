#include <iostream>
#include <stdexcept>

template <class T>
class List
{
public:
	List();
	~List();
	T& operator[] (const size_t index);
	T& at(const size_t index);
	void push_back(const T& date);
	void push_front(const T& date);
	void pop_front();
	void pop_back();
	void insert(const T& date, size_t index);
	void removeAt(const size_t index);
	void clear();
	int getSize() const { return size; }
	void swap(const size_t index1, const size_t index2);

private:
	template <class T>
	class Cell
	{
	public:
		T date;
		Cell* cNext;
		Cell(T date = T(), Cell* cNext = nullptr)
		{
			this->date = date;
			this->cNext = cNext;
		}
	};
	Cell<T>* cFirst = nullptr;
	size_t size = 0;
	Cell<T>* cLast = nullptr;
};

template <class T>
List<T>::List() {

}
template <class T>
List<T>::~List()
{
	this->clear();
}
template <class T>
void List<T>::push_back(const T& date)
{
	if (!cFirst)
	{
		cFirst = new Cell<T>(date);
		cLast = cFirst;
	}
	else
	{
		cLast->cNext = new Cell<T>(date);
		cLast = cLast->cNext;
	}
	size++;
}

template<class T>
void List<T>::push_front(const T& date)
{
	cFirst = new Cell<T>(date, cFirst);
	size++;
}

template<class T>
void List<T>::pop_front()
{
	if (cFirst)
	{
		auto next = cFirst->cNext;
		delete cFirst;
		cFirst = next;
		size--;
	}
}

template<class T>
void List<T>::pop_back()
{
	if (cLast)
	{
		auto current = cFirst;
		while (current->cNext)
		{
			cLast = current;
			current = current->cNext;
		}
		delete current;
		cLast->cNext = nullptr;
		size--;
	}
}


template<class T>
void List<T>::clear()
{
	while (size)
		this->pop_front();

}

template<class T>
void List<T>::swap(const size_t index1, const size_t index2)
{
	if (index1 != index2)
	{
		auto temp = this->operator[](index1);
		this->operator[](index1) = this->operator[](index2);
		this->operator[](index2) = temp;
	}
}


template<class T>
T& List<T>::operator[] (const size_t index)
{
	auto current = cFirst;
	for (size_t count = 0; count != index; count++) {
		current = current->cNext;
	}
	return current->date;
}

template<class T>
T& List<T>::at(const size_t index)
{
	if (index > this->size) throw std::out_of_range("arguments outside the expected range");
	return (*this)[index];
}

template<class T>
void List<T>::insert(const T& date, size_t index)
{
	if (index > this->size) throw std::out_of_range("arguments outside the expected range");
	if (index == size - 1)
		push_back(date);
	else if (index == 0)
		push_front(date);
	else
	{
		auto previous = cFirst;
		for (size_t count = 0; count != index - 1; count++) {
			previous = previous->cNext;
		}		
		previous->cNext = new Cell<T>(date, previous->cNext);;
		size++;
	}
}

template<class T>
void List<T>::removeAt(const size_t index)
{
	if (index > this->size) throw std::out_of_range("arguments outside the expected range");
	if (index == size - 1)
		pop_back();
	else if (index == 0)
		pop_front();
	else {
		auto previous = cFirst;
		for (size_t count = 0; count != index - 1; count++) {
			previous = previous->cNext;
		}
		auto remove_element = previous->cNext;
		previous->cNext = remove_element->cNext;
		delete remove_element;
		size--;
	}
}

int main() {
	List <int> one;
	one.push_back(2);
	one.push_back(4);
	one.push_back(7);
	one.push_back(5);
	one.push_back(8);
	one.swap(2, 3);
	for (size_t ii = 0; ii < one.getSize(); ii++)
	{
		std::cout << one[ii] << std::endl;
	}
}