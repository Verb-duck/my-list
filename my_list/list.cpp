#include <iostream>
#include <stdexcept>

template <class T>
class List
{
public:
	List();
	~List();
	T& operator[] (const size_t index);
	void push_back(const T& date);
	void push_front(const T& date);
	void pop_front();
	void pop_back();
	void insert(const T& date, size_t index);
	void clear();
	int getSize() const { return size; }

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
		Cell<T>* temp = new Cell<T>(date);
		cLast->cNext = temp;
		cLast = temp;
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
T& List<T>::operator[] (const size_t index)
{
	if (index > this->size) throw std::out_of_range("arguments outside the expected range");
	auto current = cFirst;
	for (size_t count = 0; count != index; count++) {
		current = current->cNext;
	}
	return current->date;
}

template<class T>
void List<T>::insert(const T& date, size_t index)
{
	if (index > this->size) throw std::out_of_range("arguments outside the expected range");
	if (index == size)
		push_back(date);
	else if (index == 0)
		push_front(date);
	else
	{
		auto previos = cFirst;
		for (size_t count = 0; count != index - 1; count++) {
			previos = previos->cNext;
		}
		auto temp = new Cell<T>(date, previos->cNext);
		previos->cNext = temp;
	}
	size++;
}

int main() {
	List <int> one;
	one.push_back(2);
	one.push_back(4);
	one.push_back(7);
	for (size_t ii = 0; ii < one.getSize(); ii++)
	{
		std::cout << one[ii] << std::endl;
	}
}