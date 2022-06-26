#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"

int size_of_lessonlist(lesson* head);

lesson** read_lessons_informations_from_file(char* file_name);

void write_lessons_informations_to_file(lesson* head_of_lessonlist, int num_of_lines);

void search_teacher_list(lesson* head_of_list, char* StudentUserName);

void search_student_list(lesson* head_of_list, char* TeacherUserName);

void search_std_grades(lesson* head_of_list, char* StudentUserName);

void search_std_grade(lesson* head_of_list, char* StudentUserName, char* TeacherUserName);

int set_new_lesson_next_of_head(lesson* head_of_list, lesson* new_lesson);

int Check_not_to_be_repeated(lesson* head_of_list, char* StudentUserName, char* TeacherUserName);

int request_course(lesson* head_of_list, char* StudentUserName, char* TeacherUserName);

int accept_requests(lesson* head_of_list, char* StudentUserName, char* TeacherUserName);

int grading(lesson* head_of_list, char* StudentUserName, char* TeacherUserName, float grade);