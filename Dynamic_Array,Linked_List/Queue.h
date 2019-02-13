#ifndef QUEUE_HEADER_INCLUDED
#define QUEUE_HEADER_INCLUDED
#include"Person.h"
class Queue
{
	struct Box
	{
		Person data;
		Box*nextBox;
		Box*prevBox;

		Box(const char*name,const char*uni,Box*nextBox=nullptr,Box*prevBox=nullptr):data(name,uni),
			nextBox(nextBox),prevBox(prevBox)
		{}
		Box(Person data, Box*nextBox = nullptr, Box*prevBox = nullptr) :data(data), nextBox(nextBox),prevBox(prevBox)
		{}
	};
public:
	Queue();
	Queue(const Queue&other);
	Queue& operator=(const Queue&other);
	~Queue();
public:
	bool isEmpty()const { return size == 0; }
	size_t numOfPeople()const { return  size; }
	Queue*clone()const { return new Queue(*this); }
public:
	bool pushBack(const Person&data);
	void popBack();
	void popFront();
	void print(std::ostream&os)const;
	Result pop(const char*name, Queue*&newQueue);
	bool merge( const Queue &other);
private:
	bool compatibleUni(const char*newPersonUni, const char*lastPersonUni);
	Box* findPerson(const char*name, int& pos)const;
private:
	void copyFrom(const Queue&other);
	void clean();
private:
	Box *firstBox;
	Box*lastBox;
	size_t size;
};
#endif
