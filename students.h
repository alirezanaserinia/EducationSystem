#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"

int size_of_stdlist(student* head);

char* read_line_from_input_file(FILE* input);

student** read_students_informations_from_file(char* file_name);

void write_students_informations_to_file(student* head_of_stdlist, int num_of_lines);

student* search_the_StdUserName(student* head_of_list, char* UserName);

int set_new_std_next_of_head(student* head_of_list, student* new_std);