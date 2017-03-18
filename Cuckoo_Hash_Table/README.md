Cuckoo Hashing Description: 
This program will read in a list of integers and hash them into tables so they can be accessed in a single machine cycle. There are two tables for numbers to hash into, each with a different hash function to determine the appropriate slot. After the primary tables hashing function is calculated, a number is placed in it if no other value is in that slot. Otherwise, the occupant of is 'evicted', and is rehashed to the other table (a value can be rehashed back and forth between tables). If any table is too full, both are expanded to the next prime number that's double their original size (i.e., a table originally of size 7 will double itself to 14, find the next prime is 21 and set its size to that).

Terminal Output Description: 
The console will display the action taken for each number in the list of integers supplied to the program. It will display to which table a number was hashed to, and to which slot. A predetermined "load factor", or lambda, is set in the code which will cause a table to roughly double in size and rehash all its values into the new table. At the end of the program, two columns of numbers are displayed to show the cells of each hash table and the values stored in it. At the end, three numbers are displayed: the final table size, the cells occupied in each table (shown as "occ1" for table 1 and "occ2" for table 2) and the percentage of cells occupied in each table which is represented as a decimal value.

Instructions:
Assure "Cuckoo Hash Table.cpp", "primes.h" and "raw_int.txt" are in the same folder.
From the terminal run: <p>
g++ Cuckoo\ Hash\ Table.cpp -std=c++11 <p>
a.out

The terminal should display the hash tables and the elements in them.