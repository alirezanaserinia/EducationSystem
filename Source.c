#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structurs_and_etc.h"
#include "students.h"
#include "teachers.h"
#include "lessons.h"

int main() {
	char* command1 = (char*)malloc(STRING_LENGTH * sizeof(char));
	char* UserName = (char*)malloc(STRING_LENGTH * sizeof(char));
	char* Password = (char*)malloc(STRING_LENGTH * sizeof(char));
	char* command2 = (char*)malloc(STRING_LENGTH * sizeof(char));
	char* std_user = (char*)malloc(STRING_LENGTH * sizeof(char));
	char* teacher_user = (char*)malloc(STRING_LENGTH * sizeof(char));
	float grade_score;
	char command_error[CHECK_INPUT_LENGTH]; // for bad input!!
	int controller; // for "logout" command 
	// std list
	student *head_of_StdList = NULL;
	head_of_StdList = (student*)malloc(sizeof(student));
	head_of_StdList->next = NULL;
	// teacher list
	teacher *head_of_TeacherList = NULL;
	head_of_TeacherList = (teacher*)malloc(sizeof(teacher));
	head_of_TeacherList->next = NULL;
	// lesson list
	lesson *head_of_LessonList = NULL;
	head_of_LessonList = (lesson*)malloc(sizeof(lesson));
	head_of_LessonList->next = NULL;
	// load students list from file
	FILE* input = fopen("std_information.txt", "r");
	int num_of_lines_from_std_file = atoi(read_line_from_input_file(input));
	student** students = (student**)malloc(sizeof(student*) * num_of_lines_from_std_file);
	students = read_students_informations_from_file("std_information.txt");
	for (int i = ZERO; i < num_of_lines_from_std_file; i++){
		set_new_std_next_of_head(head_of_StdList, students[i]);
	}
	// load teachers list from file
	FILE* input1 = fopen("teachers_information.txt", "r");
	int num_of_lines_from_tchr_file = atoi(read_line_from_input_file(input1));
	teacher** teachers = (teacher**)malloc(sizeof(teacher*) * num_of_lines_from_tchr_file);
	teachers = read_teachers_informations_from_file("teachers_information.txt");
	for (int i = ZERO; i < num_of_lines_from_tchr_file; i++) {
		set_new_tchr_next_of_head(head_of_TeacherList, teachers[i]);
	}
	// load lessons list from file
	FILE* input2 = fopen("lessons_information.txt", "r");
	int num_of_lines_from_lsn_file = atoi(read_line_from_input_file(input2));
	lesson** lessons = (lesson**)malloc(sizeof(lesson*) * num_of_lines_from_lsn_file);
	lessons = read_lessons_informations_from_file("lessons_information.txt");
	for (int i = ZERO; i < num_of_lines_from_lsn_file; i++) {
		set_new_lesson_next_of_head(head_of_LessonList, lessons[i]);
	}
	student* current_std = NULL; // any student that logged in system 
	student* temp = NULL;
	teacher* current_teacher = NULL;  // any teacher that logged in system 
	teacher* temp1 = NULL;
	while (ONE){
		controller = ZERO;
		scanf("%s", command1);
		// for students
		if (strcmp(command1,"signup_student") == ZERO){
			scanf("%s %s", UserName, Password);
			if ((search_the_StdUserName(head_of_StdList, UserName)) != NULL) //check not to be repeated
				printf("\tThere is a username like this in database\n");
			else{
				temp = (student*)malloc(sizeof(student));
				temp->UserName = strdup(UserName);
				temp->Password = strdup(Password);
				set_new_std_next_of_head(head_of_StdList, temp); // set to list
				current_std = temp; //user logged in with "signup_student" command
				printf("\tUser %s added to students\n", UserName);
			}
		}
		if ((strcmp(command1, "login_student") == ZERO) || (current_std!=NULL)) {
			if(current_std == NULL){ // user logged in with "login_student" command 
				scanf("%s %s", UserName, Password);
				temp = search_the_StdUserName(head_of_StdList, UserName); // check the username
				if (temp == NULL) {
					printf("\tUsername not found!\n");
					continue;
				}	
				else {
					if (strcmp(temp->Password, Password) == ZERO) { // check the password
						printf("\tWellcome back %s\n", UserName);
						current_std = temp;
					}
					else
						printf("\tUserName or PassWord is Wrong!!\n");
				}
			}
			if (current_std != NULL) { //user logged in system
				while (ONE) {
					scanf("%s", command2);
					if (strcmp(command2, "teachers_list") == ZERO) {
						search_teacher_list(head_of_LessonList, current_std->UserName);
						continue;
					}
					else if (strcmp(command2, "logout") == ZERO) {
						current_std = NULL;
						printf("\tyou logged out successfully\n");
						controller = ONE; // logout successfully
						break;
					}
					else if (strcmp(command2, "show_grades") == ZERO) {	//preferential 
						search_std_grades(head_of_LessonList, current_std->UserName);
						continue;
					}
					else if (strcmp(command2, "exit") == ZERO) { // save lists to file
						int num_of_lines_from_std_list = size_of_stdlist(head_of_StdList);
						write_students_informations_to_file(head_of_StdList, num_of_lines_from_std_list);
						int num_of_lines_from_tchr_list = size_of_tchrlist(head_of_TeacherList);
						write_teachers_informations_to_file(head_of_TeacherList, num_of_lines_from_tchr_list);
						int num_of_lines_from_lsn_list = size_of_lessonlist(head_of_LessonList);
						write_lessons_informations_to_file(head_of_LessonList, num_of_lines_from_lsn_list);
						exit(ZERO); 
					}
					else if (strcmp(command2, "request_course") == ZERO) { 
						scanf("%s", teacher_user);
						if (Check_not_to_be_repeated(head_of_LessonList, current_std->UserName, teacher_user)) { //check not to be repeated
							if (find_tchrUserName(head_of_TeacherList, teacher_user)) { // check that the teacher is on the teachers_list or not
								request_course(head_of_LessonList, current_std->UserName, teacher_user); // set a new losson_node successfully
							}
							else
								printf("\tThis teacher userName not found!!\n");
						}
						else
							printf("\tYou have already requested this teacher!!\n");
						continue;
					}
					else if (strcmp(command2, "show_grade") == ZERO) {
						scanf("%s", teacher_user);
						search_std_grade(head_of_LessonList, current_std->UserName, teacher_user); // search in lesson_list for show intended grade
						continue;
					}
					else {
						fgets(command_error, CHECK_INPUT_LENGTH , stdin); // if user entered a wrong command!!
						printf("\tThis order is wrong!!\n");
						continue;
					}
				}
			}
			else
				continue;
		}
		// for teachers
		if (strcmp(command1, "signup_teacher") == ZERO) {
			scanf("%s %s", UserName, Password);
			if ((search_the_TchrUserName(head_of_TeacherList, UserName)) != NULL) //check not to be repeated
				printf("\tThere is a username like this in database\n");
			else {
				temp1 = (teacher*)malloc(sizeof(teacher));
				temp1->UserName = strdup(UserName);
				temp1->Password = strdup(Password);
				set_new_tchr_next_of_head(head_of_TeacherList, temp1);// set to list
				current_teacher = temp1; //user logged in with "signup_teacher" command
				printf("\tUser %s added to teachers\n", UserName);
			}
		}
		if ((strcmp(command1, "login_teacher") == ZERO) || (current_teacher != NULL)) {
			if (current_teacher == NULL) { // user logged in with "login_teacher" command 
				scanf("%s %s", UserName, Password);
				temp1 = search_the_TchrUserName(head_of_TeacherList, UserName); // check the username
				if (temp1 == NULL) {
					printf("\tUsername not found!\n");
					continue;
				}
				else {
					if (strcmp(temp1->Password, Password) == ZERO) { // check the password
						printf("\tWellcome back %s\n", UserName);
						current_teacher = temp1;
					}
					else
						printf("\tUserName or PassWord is Wrong!!\n");
				}
			}
			if (current_teacher != NULL) { //user logged in system
				while (ONE) {
					scanf("%s", command2);
					if (strcmp(command2, "requests_list") == ZERO) { 
						search_student_list(head_of_LessonList, current_teacher->UserName);// show students who have requested this course
							continue;
					}
					else if (strcmp(command2, "logout") == ZERO) {
						current_teacher = NULL;
						printf("\tyou logged out successfully\n");
						controller = ONE; // logout successfully
						break;
					}
					else if (strcmp(command2, "accept") == ZERO) {
						scanf("%s", std_user);
						if (accept_requests(head_of_LessonList, std_user, current_teacher->UserName)) // activation student course
							printf("\tStudent accepted\n");
						else
							printf("\tThis student_userName not found!!\n");
						continue;
					}
					else if (strcmp(command2, "exit") == ZERO) { // save lists to file
						int num_of_lines_from_std_list = size_of_stdlist(head_of_StdList);
						write_students_informations_to_file(head_of_StdList, num_of_lines_from_std_list);
						int num_of_lines_from_tchr_list = size_of_tchrlist(head_of_TeacherList);
						write_teachers_informations_to_file(head_of_TeacherList, num_of_lines_from_tchr_list);
						int num_of_lines_from_lsn_list = size_of_lessonlist(head_of_LessonList);
						write_lessons_informations_to_file(head_of_LessonList, num_of_lines_from_lsn_list);
						exit(ZERO);
					}
					else if (strcmp(command2, "grade") == ZERO) { // score a grade for student by teacher
							scanf("%s %f", UserName, &grade_score);
							if (grading(head_of_LessonList, UserName, current_teacher->UserName, grade_score))
								printf("\t%s graded\n", UserName);
							else 
								printf("\tThis course must first be accepted\n");
							continue;
						}
					else {
						fgets(command_error, CHECK_INPUT_LENGTH , stdin);// if user entered a wrong command!!
						printf("\tThis order is wrong!!\n");
						continue;
					}
				}
			}
			else
				continue;
		}
		else {
			if (controller != ONE) { // no "logout" command
				fgets(command_error, CHECK_INPUT_LENGTH , stdin);// if user entered a wrong command!!
				printf("\tThis order is wrong!!\n");
				continue;
			}
		}
	} //end final while
	return ZERO;
}