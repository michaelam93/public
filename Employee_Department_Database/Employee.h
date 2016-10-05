#include <string>
using namespace std;

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

class department;	//forward declaration for below pointers and reference parameters

class employee{
private:
	int e_id;              //employee id number
	int e_dept_id;         //department for which employee is in
	string fname, lname;   //first and last name for employee
	float e_salary;        //employee salary
//helper setters
	void set_e_id(int temp_id);
	void set_e_dept_id(int temp_d_id);
	void set_e_name(string temp_fname, string temp_lname);
	void set_e_salary(float temp_salary);
//helper getters
	int get_e_id();
	int get_e_dept_id();
	string get_e_fname();
	string get_e_lname();
	float get_e_salary();
public:
	employee();
//main setter
	void set_employee_fields(int &e_curr, employee *p_e);
//friend foo's
	friend float get_employee_salary(employee *p_e, int temp_id);
	friend bool employee_exists(employee *p_e, int temp_id);
	friend void print_employees(employee *p_e, int &e_curr);
	friend float compute_avg_dept_salary(department *p_d, employee *p_e);
	friend void save_to_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend void load_from_file(employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend int switch_menu(int input, employee *p_e, department *p_d, int &e_curr, int &d_curr);
	friend void print_employees_departments(employee *p_e, department *p_d);
	friend void print_departments(employee *p_e, department *p_d, int &d_curr);
	friend void update_employee_department_db(employee *p_e, department *p_d);
	friend int find_employee(employee *p_e, int temp_id);
};