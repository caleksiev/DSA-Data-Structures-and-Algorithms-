#ifndef PERSON_HEADER_INCLUDED
#define PRESON_HEADER_INCLUDED
#include"String.h"
class Person
{
public:
	Person(const char*name, const char*uni);
public:
	const char*getName()const;
	const char*getUni()const;
private:
	bool isValidUni(const char*str)const;
private:
	String name;
	String uni;
};
#endif
