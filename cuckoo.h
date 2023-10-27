//Myesha Mahazabeen EMPLID: 24005884

#include<iostream>
#include<vector>
#include<set>
#include<stdlib.h>    // for a rand()
#include<time.h>

using namespace std;

long long power(int num, int pow);

class Cuckoo
{
private:
    string* table1;             
    string* table2;             
    float max_load_factor;      
    int size1,size2;            // how many slots are occupied
    unsigned long long max_size;               // max size of container
    string key1,key2;           
    set<string> backup;         // a set to memorize all the elements that's been inserted
    int p_idx;                  // size index
    int max_string_length;      // maximum length of string allowed to be inserted

public:
    Cuckoo();                                   // default constructor
    Cuckoo(Cuckoo&& old_obj);                   // R-Value Copy Constructor
    Cuckoo(const Cuckoo& old_obj);              // L-value copy constructor
    ~Cuckoo();                                  // destructor
    Cuckoo& operator=(Cuckoo RHS);              // copy assignment operator overloading
    void generateHash();                        
    unsigned long long hash(string s, string key);             // calculate hash of a string s
    bool search(string s);                      
    bool insert(string s, int num=1, int cnt=0);    
    void remove(string s);                      
    void insertAll();         // insert all strings from backup
};
