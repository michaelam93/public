#include "Employee.h"
#include <string>
using namespace std;

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

class employee;	//forward declaration for below pointers and reference parameters

class department{
private:
	int d_id;              //department id number
	int d_empl_arr[DMAX];  //department employee listing
	string dname;          //department name
	int d_index;           //number of employees in department
	float d_avg_salary;    //average department salary
//helper setters
	void set_d_id(int temp_id);
	void set_d_empl_arr(int &d_curr, int temp_e_id); //sets next available slot
	void set_d_name(string temp_name);
	void set_d_index();
	void set_d_avg_salary(float temp_salary);
//helper getters
	int get_d_id();
	int* get_d_empl_arr();
	string get_d_name();
	int get_d_index();
	float get_d_avg_salary();
public:
	department();
//main setter
	void set_department_fields(int &d_curr, department *p_d);
//friend foo's
	friend bool department_exists(department *p_d, int temp_id);
	friend int find_employee(employee *p_e, int temp_id);
	friend float get_employee_salary(employee *p_e, int temp_id);
	friend int find_department(department *p_d, int temp_id);
  	friend float compute_avg_dept_salary(department *p_d, employee *p_e);
	friend void save_to_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend void load_from_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend int switch_menu(int input, employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend void print_employees_departments(employee *p_e, department *p_d);
	friend void print_departments(employee *p_e, department *p_d, int &d_curr);
	friend void update_department(department &d, int &d_curr, department *p_d);
	friend void update_employee_department_db(employee *p_e, department *p_d);
};