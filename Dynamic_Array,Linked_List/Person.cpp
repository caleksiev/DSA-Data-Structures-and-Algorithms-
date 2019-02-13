#include "Person.h"

Person::Person(const char * name, const char * uni):name(name),uni(uni)
{
	//The class String allow work with nullptr,but in this class we want a valid data for every Person
	if (!name || !uni)
		throw(std::invalid_argument("Null ptr pass to Person CTOR!"));
	if (!isValidUni(uni))
		throw(std::invalid_argument("Invalid uni is pass to Person CTOR!"));
}

const char * Person::getName() const
{
	return name.getString();
}

const char * Person::getUni() const
{
	return uni.getString();
}

bool Person::isValidUni(const char * str) const
{
	return !strcmp(str, "fmi") || !strcmp(str, "unss") || !strcmp(str, "tu");
}
