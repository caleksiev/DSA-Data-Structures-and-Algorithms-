#include "Menu.h"

/*
Only through this method is ensuring a accsess to the menu
*/
 Menu & Menu::getInstance()
{
	 static Menu menu;
	 return menu;
}
 /*
Reads data from some stream and then turns to the sysytem to executes the given command
 */
 void Menu::runCommand(const char*com, std::ostream&os, std::istream&in)
 {
	 if (!strcmp(com, APPEND))
	 {
		 appendCommand(in, os);
	 }
	 else if (!strcmp(com, REMOVEL))
	 {
		 removeLastCommand(in, os);
	 }
	 else if (!strcmp(com, REMOVEF))
	 {
		 removeFirstCommand(in, os);
	 }
	 else if (!strcmp(com, REMOVE))
	 {
		 removeCommand(in, os);
	 }
	 else if (!strcmp(com, MERGE))
	 {
		 mergeCommand(in, os);
	 }
	 else if (!strcmp(com, PRINT))
	 {
		 printCommand(os);
	 }
	 else if (!strcmp(com, QUIT))
	 {
		 throw QUIT;
	 }
	 else
		 throw std::invalid_argument(UNKNOWN);
	
 }

 void Menu::skipSpaces(std::istream & in) const
 {
	 char s = in.get();
	 while (s == ' ')
		 s = in.get();
	 in.unget();
 }
 /*
 Îïèòàõ ñå íåùî äðóãî äà íàïðàâÿ ñ òåçè ìàêðîñè îòíîñíî ïîòîêà çà èçõîä, íî íå ñå
 ïîëó÷è îñîáåíî äîáðå è ãè îñòàâèõ òàêà
 */
 void Menu::removeFirstCommand(std::istream & in, std::ostream & os)
 {
	 size_t index;
	 in >> index;
	 if (!in)
		 throw std::invalid_argument(INPUT_ERROR);

	 system.removeFirstAt(index);
	 os << SUCC_FREMOVED << index << END;
 }
 void Menu::removeLastCommand(std::istream & in,std::ostream & os)
 {
	 size_t index;
	 in >> index;
	 if (!in)
		 throw std::invalid_argument(INPUT_ERROR);
	 
	 system.removeLastAt(index);
	 os << SUCC_LREMOVED << index << END;
 }

 void Menu::appendCommand(std::istream & in, std::ostream & os)
 {
	 char name[MAX_LEN_NAME];
	 char uni[MAX_LEN_UNI];
	 size_t index;

	 skipSpaces(in);
	 in.getline(name, MAX_LEN_NAME, ' ');
	 in >> uni >> index;

	 if (!in)
		 throw std::invalid_argument(INPUT_ERROR);


	 if (system.appendAt(index, Person(name, uni)))
		 os << SUCC_ADDED << index << "]" << " - " << name << "," << uni << END;
	 else
		 os << INCOMPATIBLE;
 }

 void Menu::printCommand(std::ostream & os) const
 {
	 system.printAll(os);
 }

 void Menu::mergeCommand(std::istream & in,std::ostream & os)
 {
	 size_t index1, index2;
	 in >> index1 >> index2;
	 if (!in)
		 throw std::invalid_argument(INPUT_ERROR);

	 if (system.merge(index1, index2))
		 os << SUCC_MERGE << index1 << "," << index2;
	 else
		 os << INCOMPATIBLE;
 }

void Menu::removeCommand(std::istream & in,std::ostream & os)
 {
	 char name[MAX_LEN_NAME];
	 size_t index;

	 in >> name >> index;
	 if (!in)
		 throw std::invalid_argument(INPUT_ERROR);

	 Result res = system.removeAt(index, name);
	 switch (res)
	 {
	 case REMOVE_LAST_NO_NEW_QUEUE:
		 os << SUCC_LREMOVED << index << "," << name << END;
		 break;
	 case REMOVE_FIRST_NO_NEW_QUEUE:
		 os << SUCC_FREMOVED << index << "," << name << END;
		 break;
	 case NO_SUCH_NAME_REMOVE:
		 os << NO_SUCH_NAME << "-" << name << END;
		 break;
	 case SUCCSESS_REMOVED_NEW_QUEUE:
		 os << SUCC_REMOVED_NEWQUEUE << END;
	 }
	 os << EMPTY_TEXT;
 }

/*
Empty CTOR->call to the system
*/
 Menu::Menu(){}
