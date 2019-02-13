#ifndef MENU_HEADER_INCLUDED
#define MENU_HEADER_INLCUDED
#include"System.h"
//the class is singleton
//connect the input with the system
class Menu
{
public:
	static Menu&getInstance();
	void runCommand(const char*com, std::ostream&os, std::istream&in);
private:
	void skipSpaces(std::istream&in)const;
private:
	void removeFirstCommand(std::istream&in,std::ostream & os);
	void removeLastCommand(std::istream&in,std::ostream & os) ;
	void appendCommand(std::istream&in,std::ostream & os);
	void printCommand(std::ostream & os)const;
	void mergeCommand(std::istream&in,std::ostream & os);
	void removeCommand(std::istream& in,std::ostream & os);
private:
	System system;
private:
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu();
};
#endif
