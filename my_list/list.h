#ifndef list_h
#define list_h

#include <stdexcept>


template <class T>
class List
{
public:
	List();
	~List();
	List(List<T> const& list);
	List<T>& operator =(const List<T>& list);
	T& operator[] (const size_t index);
	T operator[] (const size_t index) const;
	T& at(const size_t index);
	T at(const size_t index) const;
	void push_back(const T& date);
	void push_front(const T& date);
	void pop_front();
	void pop_back();
	void insert(const T& date, size_t index);
	void removeAt(const size_t index);
	void removeAt(const size_t index1 , const size_t index2);
	int  IndexOf(const T date);
	void clear();
	int  getSize() const { return size; }
	void swap(const size_t index1, const size_t index2);
	void sort();

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

template<class T>
List<T>::List(List<T> const& list)
{
	while (this->size != list.size)
	{
		this->push_back(list[size]);
	}
}

template<class T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (&list != this)
	{
		this->clear();
		while (this->size != list.size)
		{
			this->push_back(list[size]);
		}
	}
	return *this;
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
		if (cFirst->cNext)
		{
			auto next = cFirst->cNext;
			delete cFirst;
			cFirst = next;

		}
		else
		{
			delete cFirst;
			cFirst = nullptr;
			cLast = nullptr;
		}
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
	std::swap(this->operator[](index1), this->operator[](index2));		
}

template<class T>
void List<T>::sort()
{
		auto current = cFirst;
		auto temp = current->date;
	for (size_t ii = 0; ii < size - 1; ii++)
	{
		for (size_t jj = ii; jj < size - 1 ; jj++ )
		{
			if (current->date > current->cNext->date)
			{
				temp = current->date;
				current->date = current->cNext->date;
				current->cNext->date = temp;
			}
			current = current->cNext;
		}
		current = cFirst;		
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
T List<T>::operator[](const size_t index) const
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
	if (index > this->size || index < 0) throw std::out_of_range("arguments outside the expected range");
	return (*this)[index];
}

template<class T>
T List<T>::at(const size_t index) const
{
	if (index > this->size || index < 0) throw std::out_of_range("arguments outside the expected range");
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
	if (index > this->size || index < 0) throw std::out_of_range("arguments outside the expected range");
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

template<class T>
void List<T>::removeAt(const size_t index1, const size_t index2)
{
	if (index1 > this->size || index1 < 0 || index2 > this->size) throw std::out_of_range("arguments outside the expected range");
	if (index1 >  index2) throw std::out_of_range("arguments index1 > index2");
	size_t quantity = index2 - index1 + 1;
	if (index1 == size - 1)
		pop_back();
	else if (index1 == 0)
		while(quantity--)
			pop_front();
	else {
		auto previous = cFirst;
		for (size_t count = 0; count != index1 - 1; count++) {
			previous = previous->cNext;
		}
		auto remove_element = previous->cNext;
		while (quantity--)
		{
			previous->cNext = remove_element->cNext;
			delete remove_element;
			remove_element = previous->cNext;
			size--;
		}
	}
}

template<class T>
int List<T>::IndexOf(const T date)
{
	for (size_t ii = 0; ii < size; ii++)
	{
		if (this->operator[](ii) == date)
			return ii;
	}
	return -1;
}

#endif