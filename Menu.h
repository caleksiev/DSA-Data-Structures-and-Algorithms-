#ifndef MENU_HEADER_INCLUDED
#define MENU_HEADER_INLCUDED
#include"SystemHash.h"
//the class connect the input with the system
class Menu
{
public:	Menu(const char*fileName);
	void runCommand(const char*com, std::ostream&os, std::istream&in);
private:
	void releaseCommand(std::istream&in, std::ostream & os);
	void grabCommand(std::istream&in, std::ostream & os);
	void infoCommand(std::istream & in,std::ostream & os)const;
	void printCommand(std::ostream&os)const;
	void addCommand(std::istream & in,std::ostream & os);
	void removeCommand(std::istream&in, std::ostream & os);
	void swapCommand(std::istream& in, std::ostream & os);
private:
	SystemHash hash;
private:
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
private:
	void skipSpaces(std::istream&in)const;
};
#endif