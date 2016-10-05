#include <iostream>
#include <limits>        //used to check integer input is in valid range
#include <stdio.h>
#include <string>
#include <cstring>
#include "Department.h"
using namespace std;

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

int check_valid_int_input();
float check_valid_float_input();

void print_menu();                //prints option menu
void update_employee(employee &e, int &e_curr, employee *p_e);          //updates next employee field up to EMAX
void update_department(department &d, int &d_curr, department *p_d);    //updates next department field up to DMAX
void update_employee_department_db(employee *p_e, department *p_d);     //adds department to employee and employee
                                                                         //to department array
 /*all three "print_*(*)" functions will display an error message if theres no records  */
void print_employees(employee *p_e, int &e_curr);
void print_departments(employee *p_e, department *p_d, int &d_curr);
void print_employees_departments(employee *p_e, department *p_d);

int switch_menu(int input, employee *p_e, department *p_d, int &e_curr, int &d_curr);      //used for looping menu

bool employee_exists(employee *p_e, int temp_id);      //returns true if employee id number already existant
bool department_exists(department *p_d, int temp_id);  //returns true if department id number existant

int find_employee(employee *p_e, int temp_id);         //returns struct offset associated with an employee id number
int find_department(department *p_d, int temp_id);     //returns struct offset associated with a department id number

float get_employee_salary(employee *p_e, int temp_id); //returns individual employee salary
float compute_avg_dept_salary(department *p_d, employee *p_e);   //returns department salary for total employees
                                                                  //in department
void save_to_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);
void load_from_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);