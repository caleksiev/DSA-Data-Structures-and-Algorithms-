#include "RoundDance.h"

RoundDance::RoundDance():firstAdded(nullptr),lastAdded(nullptr),hasRound(false),size(0)
{}

RoundDance::RoundDance(const RoundDance & other): firstAdded(nullptr), lastAdded(nullptr), hasRound(false), size(0)
{
	copyFrom(other);
}
RoundDance & RoundDance::operator=(const RoundDance & other)
{
	if (this != &other)
	{
		clean();
		copyFrom(other);
	}
	return *this;
}
RoundDance::~RoundDance()
{
	clean();
}
/*
Add a new person at the end of the list,in case that the list isn't connected
*/
void RoundDance::addBack(const Person & data)
{
	if (hasRound)
		return;
	Box*newPerson = new Box(data);
	if (isEmpty())
	{
		firstAdded = lastAdded = newPerson;
		++size;
		return;
	}
	++size;
	lastAdded->rightNeighbor = newPerson;
	newPerson->leftNeighbor = lastAdded;
	lastAdded = lastAdded->rightNeighbor;
}

void RoundDance::connect()
{
	if (isEmpty() || hasRound || size < 3)
		return;
	firstAdded->leftNeighbor = lastAdded;
	lastAdded->rightNeighbor = firstAdded;
	hasRound = true;
}

void RoundDance::grab( Box  * who, const Who toGrab)
{
	checkConnection();
	checkPersonIsValid(who);
	if (toGrab == LEFT)
	{
		who->data.setHoldLeft(true);
		return;
	}
	else if (toGrab == RIGHT)
	{
		who->data.setHoldRight(true);
		return;
	}
	else//both
	{
		who->data.setHoldLeft(true);
		who->data.setHoldRight(true);
	}
}

void RoundDance::release(Box * who, const Who toGrab)
{
	checkConnection();
	checkPersonIsValid(who);
	if (toGrab == LEFT)
	{
		who->data.setHoldLeft(false);
		return;
	}
	else if (toGrab == RIGHT)
	{
		who->data.setHoldRight(false);
		return;
	}
	else//both
	{
		who->data.setHoldLeft(false);
		who->data.setHoldRight(false);
	}
}

bool RoundDance::swap( Box * who1,  Box * who2)
{
	checkConnection();
	checkPersonIsValid(who1);
	checkPersonIsValid(who2);
	//check or the persons are neighbor and they are free
	if ((!checkAreNeighbor(who1, who2) || !checkAreNeighbor(who2, who1)) &&
		(!checkHoldNoOne(who1, who2)) || !(checkHoldNoOne(who2, who1)))
		return false;
	std::swap(who1->data, who2->data);
	return true;
}

bool RoundDance::add(const Person & data,  Box *  labelLeft,  Box * labelRight)
{
	checkConnection();
	checkPersonIsValid(labelLeft);
	checkPersonIsValid(labelRight);
	if (!checkAreNeighbor(labelLeft, labelRight))//не се допуска участникът да е с гръб в хорото :)
		return false;

	Box*newPerson = new Box(data);
	lastAdded = newPerson;
	++size;

	newPerson->rightNeighbor = labelRight;
	newPerson->leftNeighbor = labelLeft;

	labelLeft->rightNeighbor = newPerson;
	labelLeft->data.setHoldRight(true);

	labelRight->leftNeighbor = newPerson;
	labelRight->data.setHoldLeft(true);

	return true;
}

bool RoundDance::remove(Box * who)
{
	checkConnection();
	if (!size)
		throw std::exception();
	checkPersonIsValid(who);
	//check if the person is free
	if (!who->data.getHoldLeft() && !who->data.getHoldRight() &&
		!who->rightNeighbor->data.getHoldLeft() && !who->leftNeighbor->data.getHoldRight())
	{
		who->rightNeighbor->leftNeighbor = who->leftNeighbor;
		who->leftNeighbor->rightNeighbor = who->rightNeighbor;
		needMovePtr(who);//in case of removing the first or the last one added
		delete who;
		--size;
		return true;
	}
	else
		return false;

}

void RoundDance::info(const Box * const who, std::ostream&os)const
{
	checkConnection();
	checkPersonIsValid(who);
	os
		<< who->leftNeighbor->data.getName()
		<< " "
		<< (who->data.getHoldLeft() ? "<" : "-")
		<< "--"
		<< (who->leftNeighbor->data.getHoldRight() ? ">" : "-")
		<< " "
		<< who->data.getName()
		<< (who->rightNeighbor->data.getHoldLeft() ? "<" : "-")
		<< "--"
		<< (who->data.getHoldRight() ? ">" : "-")
		<< " "
		<< who->rightNeighbor->data.getName() << "\n";
}

void RoundDance::print(std::ostream & os) const
{
	checkConnection();
	size_t cnt = size;
	Box*tmp = firstAdded;
	while (cnt--)
	{
		os << tmp->data.getName() << "\n";
		tmp = tmp->rightNeighbor;
	}
}


void RoundDance::copyFrom(const RoundDance & other)
{
	if (other.isEmpty())
		return;
	size_t cnt = other.size - 1;
	firstAdded = new Box(other.firstAdded->data);
	++size;
	Box*readFrom = other.firstAdded;
	Box*writeAfter = firstAdded;
	while (cnt--)
	{
		readFrom = readFrom->rightNeighbor;
		try
		{
			writeAfter->rightNeighbor = new Box(readFrom->data);
			++size;
		}
		catch (const std::bad_alloc&())
		{
			clean();
			throw;
		}
		writeAfter->rightNeighbor->leftNeighbor = writeAfter;
		writeAfter = writeAfter->rightNeighbor;
	}
	lastAdded = writeAfter;
	if (other.hasRound)
		connect();
}

void RoundDance::clean()
{
	size_t cnt = size;
	while (cnt--)
	{
		Box*temp = firstAdded;
		firstAdded = firstAdded->rightNeighbor;
		delete temp;
	}
	firstAdded = nullptr;
	lastAdded = nullptr;
	hasRound = false;
	size = 0;
}

bool RoundDance::checkPersonIsValid(const Box* const who)const
{
	return who ? true : false;
}

bool RoundDance::checkAreNeighbor(const Box * who1, const Box * who2) const
{
	return (who1->rightNeighbor->data.getName() == who2->data.getName()) ? true : false;
}

bool RoundDance::checkHoldNoOne(const Box * who1, const Box * who2) const
{
	return ((!who1->leftNeighbor->data.getHoldRight() && !who1->data.getHoldLeft() &&
		!who2->rightNeighbor->data.getHoldLeft() && !who2->data.getHoldRight())) ? true : false;
}

void RoundDance::needMovePtr(Box * who)
{
	if (firstAdded == who)
		firstAdded = who->rightNeighbor;
	if (lastAdded == who)
		lastAdded = who->rightNeighbor;
}

void RoundDance::checkConnection()const
{
	if (!hasRound)
		throw  std::exception();
}
