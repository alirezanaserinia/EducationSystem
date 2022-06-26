#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"
#include "students.h"
#include "teachers.h"
#include "lessons.h"

//this function gets a pointer to head of teachers list as argument & returns size of that list
int size_of_tchrlist(teacher* head) {
	teacher* current_tchr = head->next;
	int counter = ZERO;
	if (current_tchr == NULL)
		return ZERO;
	else {
		while (current_tchr != NULL) {
			current_tchr = current_tchr->next;
			counter++;
		}
		return counter;
	}
}

//this function reads teachers_informatinos from file
teacher** read_teachers_informations_from_file(char* file_name) {
	FILE* input;
	int i;
	if (input = fopen(file_name, "r")) {
		int num_of_lines = atoi(read_line_from_input_file(input));
		teacher** teachers = (teacher**)malloc(sizeof(teacher*) * num_of_lines);
		for (i = ZERO; i < num_of_lines; i++) {
			teacher* tchr = (teacher*)malloc(sizeof(teacher));
			tchr->UserName = read_line_from_input_file(input);
			tchr->Password = read_line_from_input_file(input);
			if (i != num_of_lines - ONE)
				tchr->next = teachers[i + ONE];
			else
				tchr->next = NULL;
			teachers[i] = tchr;
		}
		fclose(input);
		return teachers;
	}
	return NULL;
}

//this function writes teachers_informations to file
void write_teachers_informations_to_file(teacher* head_of_teacherlist, int num_of_lines) {
	teacher *temp = (teacher*)malloc(num_of_lines * sizeof(teacher));
	temp = head_of_teacherlist;
	FILE* output = fopen("teachers_information.txt", "w");
	if (output == NULL) {
		printf("Error opening file!\n");
	}
	else {
		fprintf(output, "%d\n", num_of_lines);
		for (int i = ZERO; i < num_of_lines; i++) {
			fprintf(output, "%s\n", temp->next->UserName);
			fprintf(output, "%s\n", temp->next->Password);
			temp = temp->next;
		}
		fclose(output);
	}
}

//this function searchs the teacherUser in teachersList
teacher* search_the_TchrUserName(teacher* head_of_list, char* UserName) {
	if (head_of_list == NULL)
		return NULL;
	teacher* current_teacher = head_of_list->next;
	if (current_teacher == NULL)
		return NULL;
	if (strcmp(current_teacher->UserName, UserName) == ZERO) {
		return current_teacher;
	}
	while (current_teacher->next != NULL) {
		current_teacher = current_teacher->next;
		if (strcmp(current_teacher->UserName, UserName) == ZERO)
			return current_teacher;
	}
	return NULL;
}

//this function find the teacherUser in teachersList
int find_tchrUserName(teacher* head_of_list, char* TeacherUserName) {
	int counter = ZERO;
	if (head_of_list == NULL)
		return ZERO;
	teacher* current = (teacher*)malloc(sizeof(teacher));
		current = head_of_list->next;
	if (current == NULL)
		return ZERO;
	else {
		if (strcmp(current->UserName, TeacherUserName) == ZERO) {
			return ONE;
			counter++;
		}
		else {
			while (current->next != NULL) {
				current = current->next;
				if (strcmp(current->UserName, TeacherUserName) == ZERO) {
					return ONE;
					counter++;
				}
			}
		}
	}
	if (counter == ZERO)
		return ZERO;
}

//this function sets new teacher_node to next of head
int set_new_tchr_next_of_head(teacher* head_of_list, teacher* new_tchr) {
	if (new_tchr == NULL || head_of_list == NULL)
		return ZERO;
	new_tchr->next = head_of_list->next;
	head_of_list->next = new_tchr;
	return ONE;
}
