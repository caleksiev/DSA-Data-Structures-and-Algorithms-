#ifndef SYSTEM_HEADER_INCLUDED
#define SYSTEM_HEADER_INCLUDED
#include"Queue.h"
class System
{
public:
	System();
	System(const System&other);
	System& operator=(const System&other);
	~System();
public:
	bool isEmptyAt(size_t index)const;
	size_t getSize()const;
	void removeLastAt(size_t index);
	void removeFirstAt(size_t index);
	bool appendAt(size_t index, const Person&data);
	void printAll(std::ostream& os)const;
	void printAtt(size_t index,std::ostream& os)const;
	bool merge(size_t index1, size_t index2);
	Result removeAt(size_t index, const char*name);
private:
	void setTails(size_t size);
	void setSize(size_t size);
	void setCap(size_t cap);
private:
	void copyFrom(const System&other);
	void clean();
	void clean1(Queue**& tails, size_t size);
	void resize(size_t newSize);
	void allToNull(size_t size);
private:
	void removeEmptyQueue(size_t index);
	Result removePersonAddNewQueue(size_t index, const char*name);
	void shiftQueuesIfOneIsEmpty(size_t index);
private:
	void checkIndex(size_t index)const;
private:
	Queue**tails;
	size_t size;
	size_t cap;
};
#endif
