#include <iostream>
#include <limits>        //used to check integer input is in valid range
#include <stdio.h>
#include <string>
#include <cstring>
#include "Employee.h"

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

employee::employee(){
	e_id = 0;              //employee id number
	e_dept_id = 0;         //department for which employee is in
	fname = "";
	lname = "";   //first and last name for employee
	e_salary = 0;        //employee salary
}

void employee::set_e_id(int temp_id){
	e_id = temp_id; 
	return;
}

void employee::set_e_dept_id(int temp_d_id){
	e_dept_id = temp_d_id;
	return;
}

void employee::set_e_name(string temp_fname, string temp_lname){
	fname = temp_fname;
	lname = temp_lname;
	return;
}

void employee::set_e_salary(float temp_salary){
	e_salary = temp_salary;
	return;
}

int employee::get_e_id(){
	return e_id;
}

int employee::get_e_dept_id(){
	return e_dept_id;
}

string employee::get_e_fname(){
	return fname;
}

string employee::get_e_lname(){
	return lname;
}

float employee::get_e_salary(){
	return e_salary;
}

void employee::set_employee_fields(int &e_curr, employee *p_e)
{
  if (e_curr == EMAX){
    cout << "error, no more employee records avalailable\n";
    return;
  }
  int input;
  cout << "Enter employee id: ";
  
  do{
    while (!(cin >> input)){
      cout << "invalid input\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
  } while(input < 0);
  int temp_id = input;                              //value overwritten if return hit, as counter isn't incremented
  if (employee_exists(p_e, temp_id) == true){
   cout << "error, employee record exists";
   return;
  }

  string temp_fname, temp_lname;
  float temp_salary;

  cout << "Enter employee first name: ";
  cin >> temp_fname;
  cout << "Enter employee last name: ";
  cin >> temp_lname;
  cout << "Enter employee salary: ";
  cin >> temp_salary;

  set_e_id(temp_id);
  set_e_name(temp_fname, temp_lname);
  set_e_salary(temp_salary);

  cout << "Employee " << get_e_id() << " added successfully\n";
  e_curr++;

}

int find_employee(employee *p_e, int temp_id)
{
  int i;
  for (i = 0; i < EMAX; i++){
    if (p_e->e_id == temp_id)
      return i;
    p_e++;
  }
  return -1;
}

float get_employee_salary(employee *p_e, int temp_id)
{
  int e_index = find_employee(p_e, temp_id);
  p_e += e_index;
  return p_e->e_salary;
}

void print_employees(employee *p_e, int &e_curr)
{
  int i;
  if (e_curr == 0){
    cout << "error, no employees in records\n";
    return;
  }
  printf("%-s", "-------------------------------------------------------------\n");
  printf("%-10s %-40s %-30s\n", "Empl ID", "Name", "Salary");
  printf("%-s", "-------------------------------------------------------------\n");
  for (i = 0; i < EMAX; i++){
    if (p_e->e_id != 0){
      printf(" %-10d %-20s%-20s %-30.2f\n", p_e->e_id, p_e->fname.c_str(), p_e->lname.c_str(), p_e->e_salary );
    }
    p_e++;
  }
}

bool employee_exists(employee *p_e, int temp_id)
{
  int i;
  for (i = 0; i < EMAX; i++){
    if (p_e->e_id == temp_id)
      return true;
    p_e++;
  }
  return false;
}