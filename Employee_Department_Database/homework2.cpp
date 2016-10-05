#include "homework2.h"

#define EMAX 30          //max numbers of employees
#define DMAX 10          //max numbers of employees in department and max number of departments

int main(){
	employee e_max[EMAX];
	employee *p_e = e_max;
	department d_max[DMAX];  //declares department struct array and initializes fields
	department *p_d = d_max;                     //pointer to department array
	int run = 1, input, i, e_curr = 0, d_curr = 0;	
	while (run){
	print_menu();
  input = check_valid_int_input();
	run = switch_menu(input, p_e, p_d, e_curr, d_curr);      //switch returns 0 upon successful exit
	}	
}

int check_valid_int_input()
{
  int input;
  cout << "Enter input: ";
  do{                                                      //checks for valid input
    while (!(cin >> input)){
  cout << "\ninvalid input. Enter input: ";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
  } while(input < 0);
  return input;
}

float check_valid_float_input()
{
  float input;
  cout << "Enter input: ";
  do{                                                      //checks for valid input
    while (!(cin >> input)){
  cout << "\ninvalid input. Enter input: ";
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
  } while(input < 0);
  return input;
}

int switch_menu(int input, employee *p_e, department *p_d, int &e_curr, int &d_curr)
{
  float r;
  switch(input){
    case 1:
      p_d[d_curr].set_department_fields(d_curr, p_d);
      return 1;
    case 2:
      p_e[e_curr].set_employee_fields(e_curr, p_e);
      return 1;
    case 3:
      update_employee_department_db(p_e, p_d);
      return 1;
    case 4:
      print_employees(p_e, e_curr);
      return 1;
    case 5:
      print_departments(p_e, p_d, d_curr);
      return 1;
    case 6:
      print_employees_departments(p_e, p_d);
      return 1;
    case 7:
      r = compute_avg_dept_salary(p_d, p_e);
      printf("%.2f", r);
      return 1;
    case 8:
      save_to_file(p_e, p_d, e_curr, d_curr);
      return 1;
    case 9:
      load_from_file(p_e, p_d, e_curr, d_curr);
      return 1;
    case 10:
      printf("Goodbye\n");
      return 0;                                   //program exits successfully
    default:
      fputs("Error, invalid input.\n", stderr);
      return 1;
  }
}

void print_menu()
{
  printf( "\n-------------------------------------------------------------\n"
	  "1.	Add a new department\n"
	  "2.	Add a new employee\n"
	  "3.	Add an employee to a department\n"
	  "4.	Print a list of all num_employees\n"
	  "5.	Print a list of all departments\n"
	  "6.	Print a list of all employees in a department\n"
	  "7.	Compute and print the average salary of a department\n"
	  "8.	Save the full listing to a file\n"
	  "9.	Load the full employee listing from a file\n"
	  "10.	Exit\n"
	  "-------------------------------------------------------------\n");
}

float compute_avg_dept_salary(department *p_d, employee *p_e)
{
  int temp_d_id;
  cout << "enter department id: ";
  cin >> temp_d_id;
  if (department_exists(p_d, temp_d_id) == false){
    cout << "error, department doesn't exist\n";
    return 0;
  }
  int temp_indexindex = find_department(p_d, temp_d_id);
  department *temp_index = p_d + temp_indexindex;
  int temp_d_index = temp_index->d_index; //department num of total employees
  if (temp_d_index == 0){
    cout << "error, no employees in department\n";
    return 0;
  }
  int i;
  float temp_total_salary = 0.0, temp_individual_salary = 0.0;
  for (i = 0; i < temp_d_index; i++){
    temp_individual_salary = get_employee_salary(p_e, temp_index->d_empl_arr[i]);
    temp_total_salary += (float) temp_individual_salary;
  }
  float r = temp_total_salary / (float)temp_d_index;
  return r;
}

void save_to_file(employee *p_e, department *p_d, int &e_curr, int &d_curr)
{  
  FILE *fp;
  int c, k;
  char file_name[50];
  printf("Enter file name: ");
  scanf("%s", file_name);
  
  fp = fopen(file_name, "w");
  if (!fp){
    return;
  }
  fprintf(fp, "%s\t %d\t %s\t %d\n", "employees", e_curr, "departments", d_curr);
  fprintf(fp, "%s\n", "departments: ");

  for (c = 0; c < d_curr; c++){
    fprintf(fp, " %s\t %d\t %d\n", p_d->dname.c_str(), p_d->d_id, p_d->d_index);
    for (k = 0; k < p_d->d_index; k++){
      fprintf(fp, "%d\n", p_d->d_empl_arr[k]);
    }
    p_d++;
  }

  fprintf(fp, "%s\n", "employees: ");  
  for (c = 0; c < e_curr; c++){
    fprintf(fp, " \n%s %s %d %f %d", p_e->fname.c_str(), p_e->lname.c_str(), p_e->e_id, p_e->e_salary, p_e->e_dept_id);
    p_e++;
  }
  fclose(fp);
}

void load_from_file(employee *p_e, department *p_d, int &e_curr, int &d_curr)
{
  FILE *fp;                                                               //file pointer
  char temporary[50], fname[50], lname[50];                               //temp is used for department name, others are employees
  int c, k;                                                                  //counter variables
  char file_name[50];
  printf("Enter file name: ");
  scanf("%s", file_name);
  
  fp = fopen(file_name, "r");  
  if (!fp){
    return;
  }
  
  fscanf(fp, "%*s %d %*s %d", &e_curr, &d_curr);
  fscanf(fp, "%*s"); //discard departments

  for (c = 0; c < d_curr; c++){
    fscanf(fp, "%s %d %d", temporary, &p_d->d_id, &p_d->d_index);
    for (k = 0; k < p_d->d_index; k++){
      fscanf(fp, "%d", &p_d->d_empl_arr[k]);
    }
    p_d->dname = temporary;
    p_d++;
  }

  fscanf(fp, "%*s"); //discards employees
  for (c = 0; c < e_curr; c++){
    fscanf(fp, "%s %s %d %f %d", fname, lname, &p_e->e_id, &p_e->e_salary, &p_e->e_dept_id);
    p_e->fname = fname;
    p_e->lname = lname;
    p_e++;
  }
  fclose(fp);  
}

void print_employees_departments(employee *p_e, department *p_d)
{
  int i, j;    //i used to iterate through departments using pointer arithmetic, j is used to access employee array
  int temp_id;
  cout << "\nenter department id: ";
  cin >> temp_id;

  if(!department_exists(p_d, temp_id)){
      printf("Department doesn't exist");
      return;
    }

  department *temp_dept;
  employee *temp_empl;
  temp_dept = p_d + find_department(p_d, temp_id);

  for (i = 0; i < 1; i++){
    if (temp_dept->d_id){
      printf("%-s", "-------------------------------------------------------------\n");
      printf("%-10s%-40s\n", "Dept ID", "Dept Name");
      printf("%-s", "-------------------------------------------------------------\n");
      printf(" %-10d%-40s\n", temp_dept->d_id, temp_dept->dname.c_str());
      printf("%-s", "-------------------------------------------------------------\n");
      printf("%-10s%-40s%-30s\n", " Empl ID", " Empl Name", "Salary");
      printf("%-s", "-------------------------------------------------------------\n");
      //cout << temp_employee->dname << "\n";
      for (j = 0; j < DMAX; j++){
	if (temp_dept->d_empl_arr[j]){
	  temp_empl = p_e + find_employee(p_e, temp_dept->d_empl_arr[j]);
	  printf(" %-10d%-20s%-20s%-10.2f\n", temp_dept->d_empl_arr[j], temp_empl->fname.c_str(), temp_empl->lname.c_str(), temp_empl->e_salary);	  	  
	}
      }
    }
  p_d++;  
  }  
}

void print_departments(employee *p_e, department *p_d, int &d_curr)
{
  int i, j, e;
  employee *temp_employee;

  if (d_curr == 0){
    cout << "error, no departments in records. unable to add new department\n";
    return;
  }  
  for (i = 0; i < DMAX; i++){
    if (p_d->d_id){
      printf("%-s", "-------------------------------------------------------------\n");
      printf("%-10s%-40s\n", "Dept ID", "Dept Name");
      printf("%-s", "-------------------------------------------------------------\n");
      printf(" %-10d%-40s\n", p_d->d_id, p_d->dname.c_str());
      printf("%-s", "-------------------------------------------------------------\n");
      printf("%-10s%-40s%-30s\n", " Empl ID", " Empl Name", " Salary");
      printf("%-s", "-------------------------------------------------------------\n");
      for (j = 0; j < DMAX; j++){
	if (p_d->d_empl_arr[j]){
	  temp_employee = p_e + find_employee(p_e, p_d->d_empl_arr[j]);
	  printf(" %-10d%-20s%-20s %-30.2f\n", temp_employee->e_id, temp_employee->fname.c_str(), temp_employee->lname.c_str(), temp_employee->e_salary);	  
	}   
      }
    p_d++;
    }
  }
}

void update_employee_department_db(employee *p_e, department *p_d)
{
  int temp_d_id, temp_e_id;
  cout << "Enter department id: ";
  cin >> temp_d_id;
  if (department_exists(p_d, temp_d_id) == false){
    cout << "error, department doesn't exist\n";
    return;
  }
  cout << "Enter employee id: ";
  cin >> temp_e_id;
  if (employee_exists(p_e, temp_e_id) == false){
    cout << "error, employee record doesn't exist\n";
    return;
  }  

  int e_index = find_employee(p_e, temp_e_id);
  int d_index = find_department(p_d, temp_d_id);

  p_e += e_index; //points to employee desired

  if (p_e->e_dept_id != 0){
    cout << "Employee already belongs to a department, returning to menu\n";
    return;
  }

  p_e->e_dept_id = temp_d_id;

  p_d += d_index;
  p_d->d_empl_arr[p_d->d_index] = temp_e_id;
  p_d->d_index++;

  cout << "Employee " << temp_e_id << " successfully added to department " << temp_d_id << endl;
}