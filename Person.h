#ifndef PERSON_HEADER_INCLUDED
#define PERSON_HEADER_INCLUDED
#include<string>
#include<iostream>
#include<exception>
class Person
{
public:
	Person(const std::string& name);
public:
	const std::string& getName()const;
	bool getHoldLeft()const;
	bool getHoldRight()const;
public:
	void setHoldLeft(bool status );
	void setHoldRight(bool status);
private:
	std::string name;
	bool holdLeft;//true if the "name" hold his left neighbor
	bool holdRight; // true if the "name" hold his right neighbor
};
#endif