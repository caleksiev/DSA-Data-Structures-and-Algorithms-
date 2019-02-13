#define  _CRT_SECURE_NO_WARNINGS
#ifndef STR_HEADER_INCLUDED
#define STR_HEADER_INCLUDED
#include<iostream>
#include<cstring>
#include<exception>
#include<algorithm>
#include"TempHeader.h"
class String
{
public:
	String();
	String(const char*str);
	String(const String&other);
	String&operator=(const String&other);
	~String();
public:
	const char*getString()const;
private:
	void copyFrom(const String&other);
	void clean();
private:
	void setContent(const char*str);
private:
	char*content;
};
#endif
