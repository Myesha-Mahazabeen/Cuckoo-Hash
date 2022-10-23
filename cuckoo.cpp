//Myesha Mahazabeen EMPLID: 24005884

#include "cuckoo.h"

using namespace std;

// an array to store the possible sizes 
long long P[59] = {
    2,
    3,
    5,
    11,
    17,
    37,
    67,
    131,
    257,
    521,
    1031,
    2053,
    4099,
    8209,
    16411,
    32771,
    65537,
    131101,
    262147,
    524309,
    1048583,
    2097169,
    4194319,
    8388617,
    16777259,
    33554467,
    67108879,
    134217757,
    268435459,
    536870923,
    1073741827,
    2147483659,
    4294967311,
    8589934609,
    17179869209,
    34359738421,
    68719476767,
    137438953481,
    274877906951,
    549755813911,
    1099511627791,
    2199023255579,
    4398046511119,
    8796093022237,
    17592186044423,
    35184372088891,
    70368744177679,
    140737488355333,
    281474976710677,
    562949953421381,
    1125899906842679,
    2251799813685269,
    4503599627370517,
    9007199254740997,
    18014398509482143,
    36028797018963971,
    72057594037928017,
    144115188075855881,
    288230376151711813
};

Cuckoo::Cuckoo()
{
    p_idx= 8;
    max_size = P[p_idx];
    table1 = new string[max_size];
    table2 = new string[max_size];
    for(int i=0; i<max_size; i++)
    {
        // marking the whole table empty
        table1[i] = "";
        table2[i] = "";
    }
    max_load_factor = 0.5;
    size1 = 0;
    size2 = 0;
    max_string_length = 10;     
    generateHash();             
}
Cuckoo::Cuckoo(const Cuckoo& old_obj)       // l-value copy constructor
{
    p_idx = old_obj.p_idx;
    max_size = old_obj.max_size;
    table1 = new string[max_size];
    table2 = new string[max_size];
    for(int i=0;i<max_size;i++)
    {
        table1[i] = old_obj.table1[i];
        table2[i] = old_obj.table2[i];
    }
    max_load_factor = old_obj.max_load_factor;
    size1 = old_obj.size1;
    size2 = old_obj.size2;
    max_string_length = old_obj.max_string_length;
    key1 = old_obj.key1;
    key2 = old_obj.key2;
    backup = old_obj.backup;
    
}

Cuckoo::Cuckoo(Cuckoo&& old_obj)            // r-value copy constructor
{
    p_idx = old_obj.p_idx;
    max_size = old_obj.max_size;
    table1 = new string[max_size];
    table2 = new string[max_size];
    max_load_factor = old_obj.max_load_factor;
    size1 = old_obj.size1;
    size2 = old_obj.size2;
    max_string_length = old_obj.max_string_length;
    key1 = old_obj.key1;
    key2 = old_obj.key2;
    backup =old_obj.backup;
    table1 = old_obj.table1;
    table2 = old_obj.table2;
    old_obj.table1 = NULL;   
    old_obj.table2 = NULL;
}
Cuckoo::~Cuckoo()
{
    delete[] table1;
    delete[] table2;
}

Cuckoo& Cuckoo::operator=(Cuckoo RHS)  //copy assignment operator
{
    delete []table1;
    delete []table2;
    p_idx = RHS.p_idx;
    max_size = RHS.max_size;
    table1 = new string[max_size];
    table2 = new string[max_size];
    for (int i = 0; i < max_size; i++)
    {
        table1[i] = RHS.table1[i];
        table2[i] = RHS.table2[i];
    }
    max_load_factor = RHS.max_load_factor;
    size1 = RHS.size1;
    size2 = RHS.size2;
    max_string_length = RHS.max_string_length;
    key1 = RHS.key1;
    key2 = RHS.key2;
    backup = RHS.backup;
    return *this;
}

bool Cuckoo::search(string s)
{
    if (table1[hash(s,key1)]==s || table2[hash(s,key2)]==s)
        return true;
    else 
        return false;
}
bool Cuckoo::insert(string s, int tableNum, int cnt)
{
    if(search(s)==true)     
        return 1;
    backup.insert(s);       // adding s to the list of inserted elements
    if(float(size1)/max_size > max_load_factor || float(size2)/max_size > max_load_factor)      
    {
        p_idx++;
        max_size = P[p_idx];        // choosing the next max_size from prime array P
        insertAll();                // insert all the inserted elements again.
        return 0;                   // insertion has failed
    }

    if(cnt >= max_size*2)           // insertion stuck in infinity loop. 
    {
        generateHash();             // generate new keys since old ones did not work out
        insertAll();                // insert all the inserted elements again.
        return 0;                   //  insertion has failed
    }

    
    if(tableNum == 1)       // inserting in table1
    {
        string tmp = table1[hash(s, key1)];
        table1[hash(s, key1)] = s;
        if(tmp=="")
            size1++;
        else
            insert(tmp, 2, cnt+1);
    }

    else                // inserting in table2
    {
        string tmp = table2[hash(s, key2)];
        table2[hash(s, key2)] = s;
        if(tmp=="")
            size2++;
        else
            insert(tmp, 1, cnt+1);
    }
    return 1;                   // insertion successful
}

void Cuckoo::insertAll()
{
    delete[] table1;
    delete[] table2;
    table1 = new string[max_size];
    table2 = new string[max_size];
    size1 = 0;
    size2 = 0;
    for(int i=0; i<max_size; i++)
    {
        
        table1[i] = "";
        table2[i] = "";
    }

    for(string s : backup)
    {
        // inserting every string inserted before, that we kept in backup set
        bool insert_status = insert(s);
        if(insert_status==0)
        {
            return;    // if insertion failed at  any point, don't have to insert next
        }
    }
}

void Cuckoo::remove(string s)
{
    if(table1[hash(s, key1)]==s)
        table1[hash(s, key1)] = "";

    else if(table2[hash(s, key2)]==s)
        table2[hash(s, key2)] = "";
}

void Cuckoo::generateHash()
{
    key1 = "";
    key2 = "";
    for(int i=0; i<max_string_length; i++)
    {
        key1 += char(rand()%256);        
        key2 += char(rand()%256);
    }
}

unsigned long long Cuckoo::hash(string s, string key)
{
    int chunk_size = p_idx/8;                   // chunk size = p_idx/8, where size is close to 2^p_idx
    unsigned long long hash_value = 0;
    bool flag = 0;                              
    for(int j=0; ; j++)                         
    {
        long long s_chunk = 0, key_chunk = 0;   // string chunk and key chunk
        for(int i=0; i<chunk_size; i++)         
        {
            
            int cur_idx = chunk_size*j+i;       
            if(cur_idx<s.length())           
            {
                s_chunk += int(s[cur_idx])*power(256,i);        
                key_chunk += int(key[cur_idx])*power(256,i);
            }
            else
            {
                
                flag = 1;           
                break;
            }
        }
        // after calculating value of a chunk we multiply and add it to our hash
        hash_value = (hash_value + s_chunk*key_chunk)%max_size;     
        
        if(flag==1) break;          
    }
    return hash_value;
}


long long power(int num, int pow)
{
    if(pow<=0) return 1;
    return num*power(num, pow-1);
}

