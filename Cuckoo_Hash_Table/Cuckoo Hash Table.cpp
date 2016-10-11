/*
  Author: Miguel A Martinez
  Note: A list of integers "raw_int.txt" must also be located in the same directory as this files executable for it to work
 
  References:
  [1] The Art of Computer Programming, Volume 3 (2nd edition), Section 6.4, Page 516.
  [2] http://stackoverflow.com/questions/11871245/knuth-multiplicative-hash
  [3] Cuckoo Hashing - Rasmus Pagh, Flemming Friche Rodler
  [4] https://www.cs.tau.ac.il/~shanir/advanced-seminar-data-structures-2009/bib/pagh01cuckoo.pdf
  [5] http://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "primes.h"
using namespace std;

struct Hash{
  int size;
  const float lambda = 0.5;
  float lambda1, lambda2;
  unsigned int occ1, occ2;
  vector<int> table1;
  vector<int> table2;

  Hash(){     //default parameters
    occ1 = 0;
    occ2 = 0;
    lambda1 = 0;
    lambda2 = 0;
    size = 11;
    table1.assign(11,0);
    table2.assign(11,0);
  }
  
  int hash1(int key){
    //return hash3(key);   //reference comments for hash3()
    uint32_t mult = 2654435761; //Knuth's multiple [1][2]
    return (key*mult) % size;
  }

  int hash2(int key){  //source: [5]
    //return hash3(key);   //reference comments for hash3()
    unsigned int x = key;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % size;
  }

  int hash3(int key){ //guaranteed to cause a cycle of any two hash functions this output; used for testing cycle detection
    return (key % size);
  }
  
  float get_lambda1(){
    lambda1 = (float)occ1/size;
    return lambda1;
  }

  float get_lambda2(){
    lambda2 = (float)occ2/size;
    return lambda2;
  }
  
  void print_lambda(){
    lambda1 = (float)occ1/size;
    lambda2 = (float)occ2/size;
    cout << "occ1: " << occ1 << "\t occ2: " << occ2 << endl;
    cout << "lambda1: " << lambda1 << "\t lambda2: " << lambda2 << endl;
    return;
  }

  bool lookup(int key){ //source for lookup, insert, rehash : [3][4]
    if (table1.at(hash1(key)) == key)
      return true;

    else if (table2.at(hash2(key)) == key)
      return true;

    return false;
  }
  
  void insert(int key){
    int print_key = key;
    
    if (get_lambda1() > lambda || get_lambda2() > lambda){   //load factor passed 0.5
      if (get_lambda1() > lambda)
	cout << "Table one requires rehashing with load factor: " << get_lambda1() << endl;
      else if (get_lambda2() > lambda)
	cout << "Table two requires rehashing with load factor: " << get_lambda2() << endl;
      rehash();
    }
    
    int poly = ceil(log(size));  //used to calculate ceiling of: log-base10(size)
    
    vector<int> temp {key};
    int x = key;
    int tempkey;

    if (lookup(x) == true)
      return;

    for (int i = 0; i < 100; i++){ //iterative insertion attempts
      if (table1.at(hash1(x)) == 0){
	table1.at(hash1(x)) = x;
	cout << "Element " << x << " placed into table 1, slot " << hash1(x) << endl;
	++occ1;
	return;
      }
      
      iter_swap(table1.begin()+hash1(x),temp.begin());
      tempkey = temp.front();
      swap(tempkey, x);
      
      if (table2.at(hash2(x)) == 0){
	table2.at(hash2(x)) = x;
	cout << "Element " << x << " placed into table 2, slot " << hash2(x) << endl;
	++occ2;
	return;
      }
      
      iter_swap(table2.begin()+hash2(x),temp.begin());
      tempkey = temp.front();
      swap(tempkey, x);      
    }
    
    
    
    cout << "Rehashing caused by elements: " << print_key << ", " << tempkey << ", " << x << " appearing to cause a cycle\n";
    rehash();
    insert(x); //recursive call guarantees to solve for a cycle

    return;
  }

  void rehash(){
    occ1 = 0;
    occ2 = 0;
    size = next_prime(size*2);
    
    vector<int> newtable1 (size, 0);
    vector<int> newtable2 (size, 0);

    swap(table1, newtable1);  //swap tables
    swap(table2, newtable2);
    
    vector<int>::iterator it;

    for (it = newtable1.begin(); it != newtable1.end(); it++){
      int x = *it;
      insert(x);
    }

    for (it = newtable2.begin(); it != newtable2.end(); it++){
      int y = *it;
      insert(y);
    }    

    return;
  }
  
  void hash(int key){
    insert(key);
  }
};

int main(){
  int x;
  Hash h;
  h.hash(12);
  h.hash(1);
  h.hash(23);
  FILE* fp = fopen("raw_int.txt", "r");

  while (!feof(fp)){
    fscanf(fp, "%d", &x);
    h.hash(x);
  }
  fclose(fp);
  
  for (int x = 0; x < h.size; x++){
    cout << "1: " << h.table1.at(x) << "\t \t 2:" << h.table2.at(x) << endl;
  }
  
  cout << "final table size: " << h.size << endl;
  h.print_lambda();
  
}
