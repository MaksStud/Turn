#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include<iostream>
#include"doctest.h"

using namespace std;

template<typename T>
class Turn
{
public:

	Turn(size_t s) {
		size = s;
		a = new T[size];
		index = 0;
	}

	Turn() {
		size = 10;
		a = new T[size];
		index = 0;
	}

	~Turn() {
		delete[] a;
	}

	bool isEmpty() {
		return index == 0;
	}

	bool isFull() {
		return index >= size;
	}

	virtual void add(T elem) {
		if (isFull()) {
			throw std::out_of_range("Turn full");
		}
		a[index] = elem;
		index++;
	}

	T get() {
		if (isEmpty()) {
			throw out_of_range("Turn is empty");
		}
		T elem = a[0];
		for (size_t i = 0; i < index - 1; i++) {
			a[i] = a[i + 1];
		}
		index--;
		return elem;
	}

	void fullPrint() {
		for (int i = 0; i < index; i++) {
			cout << this->a[i] << ", ";
		}
		cout << endl;
	}



protected:
	T* a;
	int index;
	size_t size;
};


template<typename T>
class PriorityQueue : public Turn<T>
{
public:
	PriorityQueue(size_t size) : Turn<T>(size) {
	}

	PriorityQueue() : Turn<T>(10) {
		this->priority = 1;
	}

	void add(T elem, int pr) {
		if (this->isFull()) {
			throw std::out_of_range("Turn full");
		}
		if (pr > this->priority) {
			for (size_t i = this->index; i > 0; i--) {
				this->a[i] = this->a[i - 1];
			}
			this->a[0] = elem;
		}
		else {
			this->a[this->index] = elem;
		}
		this->index++;
	}

private:
	int priority;
};

TEST_CASE("Turn test add and get type int") {
	Turn<int> a(2);
	a.add(4);
	CHECK(a.get() == 4);
}

TEST_CASE("Turn test add and get type char") {
	Turn<char> a(2);
	a.add('a');
	CHECK(a.get() == 'a');
}

TEST_CASE("Turn test add and get type string") {
	Turn<string> a(2);
	a.add("Hello");
	CHECK(a.get() == "Hello");
}

TEST_CASE("Priority queue add and get type int, char, string") {
	PriorityQueue<int> a;
	PriorityQueue<char> b;
	PriorityQueue<string> c;
	a.add(5, 2);
	a.add(8, 1);
	b.add('j', 2);
	b.add('o', 1);
	c.add("Word", 2);
	c.add("Hello", 1);
	CHECK(a.get() == 5);
	CHECK(a.get() == 8);
	CHECK(b.get() == 'j');
	CHECK(b.get() == 'o');
	CHECK(c.get() == "Word");
	CHECK(c.get() == "Hello");
}

/*
int main() {
	PriorityQueue<int> a;
	a.add(6, 1);
	a.add(4, 1);
	a.add(10, 1);
	a.add(8, 6);


	a.fullPrint();

	system("pause");
	return 0;
} */