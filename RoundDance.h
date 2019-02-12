#ifndef ROUNDDANCE_HEADER_INCLUDED
#define ROUNDDANCE_HEADER_INCLUDED
#include"Person.h"
#include"Helper.h"
class SystemHash;
class RoundDance
{
	friend class SystemHash;
	struct Box
	{
		Person data;
		Box*leftNeighbor;
		Box*rightNeighbor;
		Box(const Person&data,Box*const left=nullptr,Box*const right=nullptr):data(data), 
			leftNeighbor(left), rightNeighbor(right)
		{}
	};
public:
	RoundDance();
	RoundDance(const RoundDance&other);
	RoundDance&operator=(const RoundDance&other);
	~RoundDance();
public:
	bool isEmpty()const { return size == 0; }
	bool isConnect()const { return hasRound; }
	void addBack(const Person&data);
	void connect();
public:
	void grab( Box *who, const Who toGrab);
	void release(Box *who, const Who toGrab);
	bool swap( Box*who1,  Box*who2);
	bool add(const Person&data,  Box*labelLeft,  Box*labelRight);
	bool remove(Box*who);
	void info(const Box*const who,std::ostream&os)const;
	void print(std::ostream&os)const;
private:
	Box*firstAdded;//it will point to the first added person
	Box*lastAdded;//it will point to the last added peson
	bool hasRound;//it will be true,if the circle is closed(the first is connect with the last one)
	size_t size;
private:
	void copyFrom(const RoundDance&other);
	void clean();
private:
	bool checkPersonIsValid(const Box*const who)const;
	bool checkAreNeighbor(const Box*who1, const Box*who2)const;
	bool checkHoldNoOne(const Box*who1, const Box*who2)const;
	void needMovePtr(Box*who);
	void checkConnection()const;
};
#endif

