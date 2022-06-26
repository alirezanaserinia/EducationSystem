#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef structurs_and_etc
#define structurs_and_etc
#define ZERO 0
#define ONE 1
#define INACTIVE_COURSE 1
#define ACTIVE_COURSE 2
#define STRING_LENGTH 30
#define CHECK_INPUT_LENGTH 100
#define NOT_SCORED -1 //for grade

typedef struct student student;
typedef struct teacher teacher;
typedef struct lesson lesson;

// my structurs
struct student {
	char* UserName;
	char* Password;
	struct student *next; // for linked list
};

struct teacher {
	char* UserName;
	char* Password;
	struct teacher *next; // for linked list
};

struct lesson {
	char* TeacherUserName;
	char* StudentUserName;
	float Grade; 
	int active; // if active = 1 : requested lesson & if active = 2 : accepted lesson
	struct lesson *next; // for linked list
};
#endif // !structurs_and_etc

