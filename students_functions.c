#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"
#include "students.h"
#include "teachers.h"
#include "lessons.h"

//this function gets a pointer to file & reads line from file character by character & stores it as a string & returns that read line
char* read_line_from_input_file(FILE* input) {
	int line_length = ZERO;
	char* line = (char*)malloc(sizeof(char));
	*(line) = '0';
	char temp_char[ONE] = { ' ' };
	while (ONE) {
		fread(temp_char, sizeof(char), ONE, input);
		line_length++;
		line = (char*)realloc(line, sizeof(char) * line_length);
		line[line_length - ONE] = NULL;
		switch (temp_char[ZERO]) {
		case '\n':
			return line;
			break;
		case EOF:
			return line;
			break;
		default:
			line[line_length - ONE] = temp_char[ZERO];
			break;
		}
	}
}

//this function gets a pointer to head of students list as argument & returns size of that list
int size_of_stdlist(student* head) {
	student* current_std = head->next;
	int counter = ZERO;
	if (current_std == NULL)
		return ZERO;
	else {
		while (current_std != NULL) {
			current_std = current_std->next;
			counter++;
		}
		return counter;
	}
}

//this function reads students_informatinos from file
student** read_students_informations_from_file(char* file_name) {
	FILE* input;
	int i = ZERO;
	if (input = fopen(file_name, "r")) {
		int num_of_lines = atoi(read_line_from_input_file(input));
		student** students = (student**)malloc(sizeof(student*) * num_of_lines);
		for (i = ZERO; i < num_of_lines; i++) {
			student* std = (student*)malloc(sizeof(student));
			std->UserName = read_line_from_input_file(input);
			std->Password = read_line_from_input_file(input);
			if (i != num_of_lines - ONE)
				std->next = students[i + ONE];
			else
				std->next = NULL;
			students[i] = std;
		}
		fclose(input);
		return students;
	}
	return NULL;
}

//this function writes students_informations to file
void write_students_informations_to_file(student* head_of_stdlist, int num_of_lines) {
	student *temp = (student*)malloc(num_of_lines *sizeof(student));
	temp = head_of_stdlist;
	FILE* output = fopen("std_information.txt", "w");
	if (output == NULL){
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

//this function searchs the stdUser in stdList
student* search_the_StdUserName(student* head_of_list, char* UserName) {
	if (head_of_list == NULL)
		return NULL;
	student* current_std = head_of_list->next;
	if (current_std == NULL)
		return NULL;
	if (strcmp(current_std->UserName , UserName) == ZERO) {
		return current_std;
	}
	while (current_std->next!= NULL) {
		current_std = current_std->next;
		if (strcmp(current_std->UserName, UserName) == ZERO)
			return current_std;
	}
	return NULL;
}

//this function sets new std_node to next of head
int set_new_std_next_of_head(student* head_of_list, student* new_std) {
	if (new_std == NULL || head_of_list == NULL)
		return ZERO;
	new_std->next = head_of_list->next;
	head_of_list->next = new_std;
	return ONE;
}
