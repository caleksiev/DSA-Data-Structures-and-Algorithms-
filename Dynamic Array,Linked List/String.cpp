#include "String.h"
#pragma once

String::String():content(nullptr)
{
}

String::String(const char * str):content(nullptr)
{
	setContent(str);
}

String::String(const String & other):content(nullptr)
{
	copyFrom(other);
}

String & String::operator=(const String & other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

String::~String()
{
	clean();
}

const char * String::getString() const
{
	if (!content)
		return "The string is empty!\n";
	return this->content;
}

void String::copyFrom(const String & other)
{
	setContent(other.content);
}

void String::clean()
{
	delete[]content;
	content = nullptr;
}

void String::setContent(const char * str)
{
	char*oldContent = content;

	if (!str)
	{
		clean();//for now the function is private,and the problem with invalid pointed data  isn't problem
		return;
	}
	
	this->content = new char[strlen(str) + 1];
	strcpy(this->content, str);

	delete[]oldContent;//if everything is ok
}
