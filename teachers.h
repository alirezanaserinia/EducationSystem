#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"

int size_of_tchrlist(teacher* head);

teacher** read_teachers_informations_from_file(char* file_name);

void write_teachers_informations_to_file(teacher* head_of_teacherlist, int num_of_lines);

teacher* search_the_TchrUserName(teacher* head_of_list, char* UserName);

int find_tchrUserName(teacher* head_of_list, char* TeacherUserName);

int set_new_tchr_next_of_head(teacher* head_of_list, teacher* new_tchr);