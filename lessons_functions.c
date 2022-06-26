#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"
#include "students.h"
#include "teachers.h"
#include "lessons.h"

// this function gets a pointer to head of lessons list as argument & returns size of that list
int size_of_lessonlist(lesson* head) {
	lesson* current_lesson = head->next;
	int counter = ZERO;
	if (current_lesson == NULL)
		return ZERO;
	else {
		while (current_lesson != NULL) {
			current_lesson = current_lesson->next;
			counter++;
		}
		return counter;
	}
}

// this function reads lessons_informatinos from file
lesson** read_lessons_informations_from_file(char* file_name) {
	FILE* input;
	int i = ZERO;
	if (input = fopen(file_name, "r")) {
		int num_of_lines = atoi(read_line_from_input_file(input));
		lesson** lessons = (lesson**)malloc(sizeof(lesson*) * num_of_lines);
		for (i = ZERO; i < num_of_lines; i++) {
			lesson* lsn = (lesson*)malloc(sizeof(lesson));
			lsn->TeacherUserName = read_line_from_input_file(input);
			lsn->StudentUserName = read_line_from_input_file(input);
			lsn->Grade =atof(read_line_from_input_file(input));
			lsn->active = atoi(read_line_from_input_file(input));
			if (i != num_of_lines - ONE)
				lsn->next = lessons[i + ONE];
			else
				lsn->next = NULL;
			lessons[i] = lsn;
		}
		fclose(input);
		return lessons;
	}
	return NULL;
}

// this function writes lessons_informations to file
void write_lessons_informations_to_file(lesson* head_of_lessonlist, int num_of_lines) {
	lesson *temp = (lesson*)malloc(num_of_lines * sizeof(lesson));
	temp = head_of_lessonlist;
	FILE* output = fopen("lessons_information.txt", "w");
	if (output == NULL) {
		printf("Error opening file!\n");
	}
	else {
		fprintf(output, "%d\n", num_of_lines);
		for (int i = ZERO; i < num_of_lines; i++) {
			fprintf(output, "%s\n", temp->next->TeacherUserName);
			fprintf(output, "%s\n", temp->next->StudentUserName);
			fprintf(output, "%.2f\n", temp->next->Grade);
			fprintf(output, "%d\n", temp->next->active);
			temp = temp->next;
		}
		fclose(output);
	}
}

// "teachers_list" command: this function finds nodes(teacher_user) that their std_users equal to std_users have come as arguments to function
void search_teacher_list(lesson* head_of_list, char* StudentUserName) {
	int counter = ZERO;
	if (head_of_list == NULL)
		return NULL;
	lesson* current_lesson = head_of_list->next;
	printf("Your teachers :\n");
	if (current_lesson == NULL)
		return NULL;
	if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (current_lesson->active == ACTIVE_COURSE)) {
		printf("\t%s\n", current_lesson->TeacherUserName);
		counter++;
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (current_lesson->active == ACTIVE_COURSE)) {
			printf("\t%s\n", current_lesson->TeacherUserName);
			counter++;
		}
	}
	if(counter == ZERO)
		printf("\tNot found any teacher \n");
	else
		printf("\t***************\n");
}

// "show_grades" command: for all of the lessons
void search_std_grades(lesson* head_of_list, char* StudentUserName) {
	int counter = ZERO;
	int grade_number = ZERO;
	float sum = ZERO;
	float temp;
	if (head_of_list == NULL)
		return NULL;
	lesson* current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return NULL;
	printf("Lessons grades : \n");
	if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (current_lesson->active == ACTIVE_COURSE)) {
		if (current_lesson->Grade == NOT_SCORED) {
			printf("\tMR.%s has not yet scored a grade!!\n", current_lesson->TeacherUserName);
			counter++;
		}
		else {
			printf("\t%s\t%.2f\n", current_lesson->TeacherUserName, current_lesson->Grade);
			sum = current_lesson->Grade;
			counter++;
			grade_number++;
		}
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (current_lesson->active == ACTIVE_COURSE)) {
			if (current_lesson->Grade == NOT_SCORED) {
				printf("\tMR.%s has not yet scored a grade!!\n", current_lesson->TeacherUserName);
				counter++;
				continue;
			}
			else {
				printf("\t%s\t%.2f\n", current_lesson->TeacherUserName, current_lesson->Grade);
				temp = current_lesson->Grade;
				sum += temp;
				counter++;
				grade_number++;
			}
		}
	}
	if (counter == ZERO)
		printf("\tAny lesson not found \n");
	if (grade_number != ZERO) {
		printf("\t***************\n");
		printf("\tGPA : %.2f\n", ((float)sum / grade_number));
	}
}

// "show_grade" command: for one lesson
void search_std_grade(lesson* head_of_list, char* StudentUserName, char* TeacherUserName) {
	int counter = ZERO;
	if (head_of_list == NULL)
		return NULL;
	lesson* current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return NULL;
	if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
		if (current_lesson->Grade == NOT_SCORED) {
			printf("\tMR.%s has not yet scored a grade!!\n", current_lesson->TeacherUserName);
			counter++;
		}
		else {
			printf("\tYour grade is %.2f\n", current_lesson->Grade);
			counter++;
		}
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
			if (current_lesson->Grade == NOT_SCORED) {
				printf("\tMR.%s has not yet scored a grade!!\n", current_lesson->TeacherUserName);
				counter++;
				continue;
			}
			else {
				printf("\tYour grade is %.2f\n", current_lesson->Grade);
				counter++;
			}
		}
	}
		if (counter == ZERO)
			printf("\tAny lesson not found \n");
}

// "requests_list" command: this function finds nodes(student_user) that their teacher_users equal to teacher_users have come as arguments to function
void search_student_list(lesson* head_of_list, char* TeacherUserName){
	int counter = ZERO;
	if (head_of_list == NULL)
		return NULL;
	lesson* current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return NULL;
	if ((strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO) && (current_lesson->active == INACTIVE_COURSE)) {
		printf("\t%s\n", current_lesson->StudentUserName);
		counter++;
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO) && (current_lesson->active == INACTIVE_COURSE)) {
			printf("\t%s\n", current_lesson->StudentUserName);
			counter++;
		}
	}
	if (counter == ZERO)
		printf("\tNot found any student \n");
}

// this function sets new lsn_node to next of head
int set_new_lesson_next_of_head(lesson* head_of_list, lesson* new_lesson) {
	if (new_lesson == NULL || head_of_list == NULL)
		return ZERO;
	new_lesson->next = head_of_list->next;
	head_of_list->next = new_lesson;
	return ONE;
}

// this function checks that a student does not request a teacher twice or more
int Check_not_to_be_repeated(lesson* head_of_list, char* StudentUserName, char* TeacherUserName) {
	int check = ZERO; // if check = 0 : Duplicate node not found
	if (head_of_list == NULL)
		return NULL;
	lesson* current_lesson = (lesson*)malloc(sizeof(lesson));
	current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return NULL;
	if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
		check++;
		return ZERO;
	}
	while (current_lesson->next!=NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
			check++;
			return ZERO;
		}
	}
	if (check == ZERO)
		return ONE;

}

// this function set a new node by default(grade , active , ...) & with stdUser and tchrUser to lesson list 
int request_course(lesson* head_of_list, char* StudentUserName, char* TeacherUserName) {
	lesson* temp = head_of_list;
	lesson* new_lesson;
	new_lesson = (lesson*)malloc(sizeof(lesson));
	new_lesson->TeacherUserName = strdup(TeacherUserName);
	new_lesson->StudentUserName = strdup(StudentUserName);
	new_lesson->Grade = NOT_SCORED; // default
	new_lesson->active = INACTIVE_COURSE; // requested lesson
	new_lesson->next = NULL;
	if (set_new_lesson_next_of_head(temp, new_lesson)) {
		printf("\tYou added to this course\n");
		return ONE;
	}
	else
		return ZERO;
}

// this function actives course
int accept_requests(lesson* head_of_list, char* StudentUserName, char* TeacherUserName) {
	int counter = ZERO;
	if (head_of_list == NULL)
		return ZERO;
	lesson* current_lesson = (lesson*)malloc(sizeof(lesson));
		current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return ZERO;
	if ((strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO) &&  (current_lesson->active == INACTIVE_COURSE)) {
		if (strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) {
			current_lesson->active = ACTIVE_COURSE;
			counter++;
			return ONE;
		}
		else 
			return ZERO;
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO) && (current_lesson->active == INACTIVE_COURSE)) {
			if (strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) {
				current_lesson->active = ACTIVE_COURSE;
				counter++;
				return ONE;
			}
			else 
				return ZERO;
		}
	}
	if (counter == ZERO)
		return ZERO;
}

// this function enters the score that the teacher has given for student
int grading(lesson* head_of_list, char* StudentUserName, char* TeacherUserName, float grade) {
	int counter = ZERO;
	if (head_of_list == NULL)
		return ZERO;
	lesson* current_lesson = (lesson*)malloc(sizeof(lesson));
	current_lesson = head_of_list->next;
	if (current_lesson == NULL)
		return ZERO;
	if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
		if (current_lesson->active == ACTIVE_COURSE) {
			current_lesson->Grade = grade;
			counter++;
			return ONE;
		}
		else 
			return ZERO;		
	}
	while (current_lesson->next != NULL) {
		current_lesson = current_lesson->next;
		if ((strcmp(current_lesson->StudentUserName, StudentUserName) == ZERO) && (strcmp(current_lesson->TeacherUserName, TeacherUserName) == ZERO)) {
			if (current_lesson->active == ACTIVE_COURSE) {
				current_lesson->Grade = grade;
				counter++;
				return ONE;
			}
			else
				return ZERO;
		}
	}
	if (counter == ZERO)
		return ZERO;
}

