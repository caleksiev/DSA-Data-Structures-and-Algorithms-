#include "Person.h"

Person::Person(const std::string& name):name(name)
{
	setHoldLeft(true);
	setHoldRight(true);
}

const std::string& Person::getName() const
{
	return name;
}

bool Person::getHoldLeft() const
{
	return holdLeft;
}

bool Person::getHoldRight() const
{
	return holdRight;
}



void Person::setHoldLeft(bool status)
{
	holdLeft = status;
}

void Person::setHoldRight(bool status)
{
	holdRight = status;
}


