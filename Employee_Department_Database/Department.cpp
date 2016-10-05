#include "Department.h"

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

#include <iostream>
#include <limits>        //used to check integer input is in valid range
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

department::department()
{
	d_id = 0;              //department id number
	for (int i = 0; i < DMAX; i++){
		d_empl_arr[i] = 0;
	}
	dname = "";          //department name
	d_index = 0;           //number of employees in department
	d_avg_salary = 0;    //average department salary	

}

void department::set_department_fields(int &d_curr, department *p_d)
{
  if (d_curr == DMAX){
      cout << "error, no more department records available\n";
      return;
  }
  int temp_id, input;
  cout << "Enter department id: ";
  cin >> input;

  temp_id = input;  

  if (department_exists(p_d, temp_id) == true){
      cout << "error, department record exists";   //also works if input is 0
      return;
  }     

  cout << "Enter department name: ";
  cin >> dname;
  d_id = temp_id;
  d_curr++;
}

void department::set_d_id(int temp_id){
  d_id = temp_id;
  return;
}

void department::set_d_name(string temp_name){
  dname = temp_name;
  return;
}

void department::set_d_index(){
  d_index++;
  return;
}

void department::set_d_avg_salary(float temp_salary){
  d_avg_salary = temp_salary;
  return;
}

int department::get_d_id(){
  return d_id;
}

int* department::get_d_empl_arr(){
  return d_empl_arr;

}

void department::set_d_empl_arr(int &d_curr, int temp_e_id){ //sets next available slot
  if (d_curr == DMAX)
    return;
  d_empl_arr[d_curr] = temp_e_id;
  d_curr++;
  return;     
}

string department::get_d_name(){
  return dname;
}
int department::get_d_index(){
  return d_index;
}

float department::get_d_avg_salary(){
  return d_avg_salary;
}

bool department_exists(department *p_d, int temp_id)
{
  int i;
  for (i = 0; i < DMAX; i++){
    if (p_d->d_id == temp_id)
      return true;
    p_d++;
  }
  return false;
}


int find_department(department *p_d, int temp_id)
{
  int i;
  for (i = 0; i < DMAX; i++){
    if (p_d->d_id == temp_id)
      return i;
    p_d++;
  }
  return -1;
}