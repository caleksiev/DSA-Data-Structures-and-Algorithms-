#include "System.h"

/*
The system always starts with one empty queue
*/
System::System():tails(nullptr), size(1), cap(2)
{
	setTails(2);
	tails[0] = new Queue();
}

/*
Cpy CTOR
*/
System::System(const System & other):tails(nullptr),size(0),cap(0)
{
	copyFrom(other);
}

/*
Assignment operator
*/
System & System::operator=(const System & other)
{
	if (this != &other)
	{
		clean();
		copyFrom(other);
	}
	return *this;
}

/*
DCTOR
*/
System::~System()
{
	clean();
}

/*
Check whether the queue is empty or not at some index in container
If the index is invalid->std::out_of_range exception is throwing
[O(1)]
*/
bool System::isEmptyAt(size_t index) const
{
	checkIndex(index);
	return tails[index]->isEmpty();
}
/*
Remove the person at the end of the queue at some index in container
If the index is invalid->std::out_of_range exception is throwing
If the queue is empty after this operation all other queues after the
empty queue are shift back with one position
[O(1)+c]
*/
void System::removeLastAt(size_t index)
{
	checkIndex(index);

	tails[index]->popBack();

	shiftQueuesIfOneIsEmpty(index);
}
/*
Remove the person in the beginning of the queue at some index in container
If the index is invalid->std::out_of_range exception is throwing
If the queue is empty after this operation all other queues after the
empty queue are shift back with one position(c)
[O(1)+c]
*/
void System::removeFirstAt(size_t index)
{
	checkIndex(index);

	tails[index]->popFront();

	shiftQueuesIfOneIsEmpty(index);
}
/*
Add new person with his data at the end of the queue at some index in the container
If the index is invalid->std::out_of_range exception is throwing
[O(1)]
*/
bool System::appendAt(size_t index,const Person & data)
{

	checkIndex(index);
	return tails[index]->pushBack(data);
}
/*
Print info about all queues in the container and about every person in the queues on some stream
If the stream is not okay the method does nothing
[O(n^2)]
*/
void System::printAll(std::ostream & os) const
{
	if (!os)
		return;
	os << "There are " << size << " queues:\n";
	for (size_t i = 0; i < size; ++i)
	{
		os << "Line" << i << ":";
		tails[i]->print(os);
	}
}
/*
Print info about every person in the queue at some index in the container on some stream
If the stream is not okay the method does nothing
If the index is invalid->std::out_of_range exception is throwing
[O(n)]
*/
void System::printAtt(size_t index, std::ostream& os) const
{
	if (!os)
		return;
	checkIndex(index);

	tails[index]->print(os);
}
/*
Merge two queues in the container
If the indexes are invalid->std::out_of_range exception is throwing
If the merge is succsessfull ->remove the second queue(shift back other queue)
[O(n^2)] :(
*/
bool System::merge(size_t index1, size_t index2)
{

	checkIndex(index1);
	checkIndex(index2);
	if (index1 == index2)
		return true;

	if (tails[index1]->merge(*tails[index2]))
	{
		removeEmptyQueue(index2);
		return true;
	}
	return false;
	
}/*
 Remove person from queue[index]
 If the indexes are invalid->std::out_of_range exception is throwing
 [O(n)+c]
 */
Result System::removeAt(size_t index, const char * name)
{
	checkIndex(index);

	return removePersonAddNewQueue(index, name);
}
/*
Return the count of the queues in the system
[O(1)]
*/
size_t System::getSize() const
{
	return size;
}
/////////////////////////////////////////
/*
PRIVATE METHODS
*/
////////////////////////////////////////

/*
SETTER
*/
void System::setTails(size_t size)
{
	this->tails = new Queue*[size];
	allToNull(size);
}

void System::setSize(size_t size)
{
	this->size = size;
}

void System::setCap(size_t cap)
{
	this->cap = cap;
}

void System::copyFrom(const System & other)
{
	setTails(other.cap);

	try
	{
		for (size_t i = 0; i < other.size; ++i)
		{
			tails[i] = other.tails[i]->clone();
		}
	}
	catch (const std::bad_alloc&)
	{
		clean();
		throw;
	}
	setSize(other.size);
	setCap(other.cap);
}

void System::clean()
{
	for (size_t i = 0; i < cap; ++i)
	{
		delete tails[i];
	}
	delete[]tails;
	tails = nullptr;
	size = 0;
	cap = 0;
}

void System::clean1(Queue ** &tails, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		delete tails[i];
	delete[] tails;
	tails = nullptr;
}

void System::resize(size_t newCap)
{
	Queue**tempTails = tails;

	setTails(newCap);

	size_t Size = std::min(newCap, size);

	try
	{
		for (size_t i = 0; i < Size; ++i)
		{
			tails[i] = tempTails[i]->clone();
		}
	}
	catch (const std::bad_alloc&)
	{
		clean();
		tails = tempTails;
		throw;
	}

	clean1(tempTails, cap);
	setCap(newCap);
}

void System::allToNull(size_t size)
{
	for (size_t i = 0; i < size; ++i)
		tails[i] = nullptr;
}
//preindexing all queue from the empty one
void System::removeEmptyQueue(size_t index)
{
	if (size == 1)
	{
		--size;
		return;
	}
	for (size_t i = index; i < size - 1; ++i)
	{
		std::swap(tails[i], tails[i + 1]);
	}
	--size;//zero it should't be pass
}
/*
Try to remove the person from queue[index]
If the pop is succsessfull add all people after the removed person in the container as a new queue
If the queue is empty after this operation->remove it from container
*/
Result System::removePersonAddNewQueue(size_t index,const char*name)
{
	Queue*newQueue;
	Result res = tails[index]->pop(name, newQueue);
	if (newQueue)
	{

		if (size == cap)
		{
			size_t newSize = size * 2;
			resize(newSize);
		}
		tails[size] = newQueue;
		++size;
	}
	shiftQueuesIfOneIsEmpty(index);
	return res;
}

void System::shiftQueuesIfOneIsEmpty(size_t index)
{
	if (isEmptyAt(index))
	{
		removeEmptyQueue(index);
	}
}

void System::checkIndex(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("Invalid index for accsessing the collection!\n");
}
