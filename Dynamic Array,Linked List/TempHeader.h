#ifndef TEMP_HEADER_INCLUDED
#define TEMP_HEADER_INCLUDED

const size_t MAX_LEN_NAME = 100;
const size_t MAX_LEN_UNI = 5;
const unsigned short MAX_LEN = 200;

enum Result
{
	REMOVE_LAST_NO_NEW_QUEUE = 0,
	REMOVE_FIRST_NO_NEW_QUEUE,
	NO_SUCH_NAME_REMOVE,
	SUCCSESS_REMOVED_NEW_QUEUE
};
//commands
#define APPEND "append"
#define REMOVEL "removeLast"
#define REMOVEF "removeFirst"
#define REMOVE "remove"
#define MERGE "merge"
#define QUIT "quit"
#define PRINT "print"

//results message
#define SUCC_FREMOVED "The first person was removed from the queue with index "
#define SUCC_LREMOVED "The last person was removed from the queue with index "
#define SUCC_ADDED "It was added a person at the end of the queue["
#define INCOMPATIBLE "Incompatible people!\n"
#define EMPTY_TEXT ""
#define NO_SUCH_NAME "There isn't a person in the queue with that name "
#define SUCC_REMOVED_NEWQUEUE "The person was removed from the queue and all people behind him created one new queue "
#define SUCC_MERGE "The two queues were succsessfully merged with indexes "
//exceptions message
#define UNKNOWN "Unknown command!\n"
#define INPUT_ERROR "Error with the iostream!One possible cause is that isn't pass a valid type!\n"
#define END "!\n"


#endif
