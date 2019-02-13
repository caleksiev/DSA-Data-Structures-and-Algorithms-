#include "Queue.h"
/*
CTOR
Creates an empty queue
*/
Queue::Queue():firstBox(nullptr),lastBox(nullptr),size(0)
{

}
/*
CPY CTOR
*/
Queue::Queue(const Queue & other) : firstBox(nullptr), lastBox(nullptr), size(0)
{
	copyFrom(other);
}
/*
Assignment operator
*/
Queue & Queue::operator=(const Queue & other)
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
Queue::~Queue()
{
	clean();
}

/*
Remove the last person in the queue
If the queue is empty->std::out_of_range exception 
If memory allocation fails->std::bad_alloc 
[O(1)]
*/
void Queue::popBack()
{
	if (isEmpty())
		throw std::out_of_range("The Queue is already empty!\n");


	if (numOfPeople() == 1)
	{
		delete firstBox;
		firstBox = lastBox = nullptr;
		--size;
		return;
	}
	//save where is the last box 
	Box*destroyer = lastBox;
	//change the end of the queue
	lastBox = lastBox->prevBox;
	lastBox->nextBox = nullptr;
	//delete the person
	delete destroyer;
	//decrease the people in the queue
	--size;
}
/*
Remove the first person in the queue
If the queue is empty->std::out_of_range exception
If memory allocation fails->std::bad_alloc
[O(1)]
*/
void Queue::popFront()
{
	//already have this method
	if (isEmpty() || numOfPeople() == 1)
	{
		popBack();
		return;
	}
	//save where is the first box 
	Box*destroyer = firstBox;
	//change the start of the queue
	firstBox = firstBox->nextBox;
	firstBox->prevBox = nullptr;
	//delete the person
	delete destroyer;
	//decrease the people in the queue
	--size;
}
/*
Add new person at the end of the queue,if he has compatible uni with the last one 
If memory allocation fails->std::bad_alloc
[O(1)]
*/
bool Queue::pushBack(const Person & data)
{
	if (!isEmpty())
	{
		if (!compatibleUni(data.getUni(),lastBox->data.getUni()))
			return false;
		//create the new person
		Box* newPerson = new Box(data);
		//connect the new person with the previous one
		newPerson->prevBox = lastBox;
		//and connect previous one with the new person
		lastBox->nextBox = newPerson;
		//change the end of the queue
		lastBox = newPerson;
		//increase people in the queue
		++size;
		return true;
	}
	//the queue is empty

	//create the new person
	Box* newPerson = new Box(data);
	//connect the end and start of the queue with the new person
	lastBox = firstBox = newPerson;
	//increase people in the queue
	++size;
	return true;
}

/*
Print info about all people in the queue on some stream
If the stream in't ok the method does nothing
[O(n)]
*/
void Queue::print(std::ostream&os) const
{
	if (!os)
		return;
	Box*temp = firstBox;
	if (!temp)
	{
		os << "The queue is empty!\n";
		return;
	}
	os << "There are " << size << " people!\n";
	while (temp->nextBox)
	{
		os <<"("<< temp->data.getName() << ", " << temp->data.getUni()<<")"<< " - ";
		temp = temp->nextBox;
	}
	//without '-' and add new line
	os << "(" << temp->data.getName() << ", " << temp->data.getUni() << ")"<<"\n";

}
/*
If the method finds a person with such name,removes him from the queue and
if he isn't at the  or in the beginning of the queue, all people after him
creates a new queue and this queue is saved to the second argument of the method.
Otherwise the function dosn't do nothing.
Method return enum type!
[O(n)]->because of findPersonf method
*/
Result Queue::pop(const char * name, Queue *& newQueuePar)
{
	int findAt;//the index where the person will be find at the queue,-1 if the person isn't found
	Box*where = findPerson(name, findAt);//return a ptr to the found box,nullptr if the person isn't found
	if (!where)//the person isn't found,new queue isn'created
	{
		newQueuePar = nullptr;
		return NO_SUCH_NAME_REMOVE;
	}
	if (where == firstBox)//just remove the last person in the queue,new queue isn'created
	{
		popFront();
		newQueuePar = nullptr;
		return REMOVE_FIRST_NO_NEW_QUEUE;
	}
	if (where == lastBox)//just remove the first person in the queue,new queue isn'created
	{
		popBack();
		newQueuePar = nullptr;
		return REMOVE_LAST_NO_NEW_QUEUE;
	}
	//here the person is found and he isn't the firts or the last one in the queue

	//1)find the lastBox for the new queue,which is the lastBox for the old queue
	Box*newEnd = lastBox;
	//2)move the old lastBox before the box we want to remove
	lastBox = where->prevBox;
	//3)find the firstBox for the new queue,which is the box after the box we want to remove
	Box*newStart = lastBox->nextBox->nextBox;
	//4) create the new queue
	Queue newQueue;
	newQueue.firstBox = newStart;
	newQueue.lastBox = newEnd;
	newQueue.size = (size - findAt) - 1;;//the new box queue is the current at the queue - the removed one - index where we found the person

	//5)return the result
	try
	{
		newQueuePar = new Queue(newQueue);
	}
	catch (const std::bad_alloc&)//if allocation is not ok,reset the old queue
	{
		lastBox = newEnd;
		throw;
	}
	//6)everything is ok,null the pointers before and after the pesron and then remove him and change the size 
	newStart->prevBox = nullptr;
	lastBox->nextBox = nullptr;
	delete where;
	size -= (newQueue.size+1);

	return SUCCSESS_REMOVED_NEW_QUEUE;
}
/*
Append other queue to the current queue
[O(n)]->because of copy
*/
bool Queue::merge( const Queue  & other)
{
	if (!compatibleUni(other.firstBox->data.getUni(), lastBox->data.getUni()))
		return false;
	if (other.isEmpty())
		return true;

	Queue*cpy = new Queue(other);
	if (isEmpty())
	{
		firstBox = cpy->firstBox;
		lastBox = cpy->lastBox;
		size += cpy->size;
		return true;
	}
	//connect the start of the new queue with the end of the current one
	cpy->firstBox->prevBox = lastBox;
	//connect the end of the current queue with the start of the new one
	lastBox->nextBox = cpy->firstBox;

	//remove the start of the new queue
	cpy->firstBox = firstBox;

	//change the end of the current queue
	lastBox = cpy->lastBox;
	//increase the size of people 
	size += cpy->size;

	return true;
}
//check whether two uni are compatible
bool Queue::compatibleUni(const char*newPersonUni, const char*lastPersonUni)
{

	if (!strcmp(newPersonUni, "fmi"))
	{
		if (!strcmp(lastPersonUni, "unss"))
			return false;
	}
	else if (!strcmp(newPersonUni, "tu"))
	{
		if (!strcmp(lastPersonUni, "fmi"))
			return false;
	}

	else if (!strcmp(newPersonUni, "unss"))
	{
		if (!strcmp(lastPersonUni, "tu"))
			return false;
	}
	else
		return false;
	return true;
}

/*
Search for person with name in the queue,and return the box and the index where he is found(nullptr and -1 if he isn't)
*/
typename Queue ::Box * Queue::findPerson(const char * name,int& pos) const
{
	int cnt = -1;
	Box*temp = firstBox;
	while (temp)
	{
		++cnt;
		if (!strcmp(name, temp->data.getName()))
		{
			pos = cnt;
			return temp;
		}

		temp = temp->nextBox;
	}
	pos = -1;
	return temp;
}

void Queue::copyFrom(const Queue & other)
{
	if (!other.isEmpty())
	{
		try
		{
			firstBox = new Box(other.firstBox->data);
			firstBox->prevBox = nullptr;

			Box*readFrom = other.firstBox;
			Box*writeAfter = firstBox;

			while (readFrom->nextBox)//while there is what to copy we copy :)
			{
				readFrom = readFrom->nextBox;//move to the next box from where we have to copy
				writeAfter->nextBox = new Box(readFrom->data);//create the new box and connect it with previous one
				writeAfter->nextBox->prevBox = writeAfter;//move the previous ptr of the new box to the previous box
				writeAfter = writeAfter->nextBox;//move to the next box where to copy
			}
			lastBox = writeAfter;
		}
		catch (const std::bad_alloc&)
		{
		
			clean();
			throw;
			
		}
	}
	size = other.size;
}

void Queue::clean()
{
	Box*destroyer = firstBox;
	while (destroyer)
	{
		firstBox = firstBox->nextBox;
		delete destroyer;

		destroyer = firstBox;
	}
	firstBox = nullptr;
	lastBox = nullptr;
	size = 0;
}
