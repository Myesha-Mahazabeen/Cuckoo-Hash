//Myesha Mahazabeen EMPLID: 24005884

#include "cuckoo.h"
#include<vector>

using namespace std;

int main()
{
    Cuckoo a;
    vector<string> items;
    set<string> it;
    srand(time(0));
    for(int i=0; i<100000; i++)
    {
        string str = "";
        int len = 1+rand()%10;
        for(int j=0; j<len; j++)
            str += char(rand()%256);
        
        a.insert(str);
        items.push_back(str);
        it.insert(str);
    }
    Cuckoo b = a;       // copy constructor
    Cuckoo c;           // assignment opertator
    c=a;
    for(int i=0; i<100000; i++)
        if(a.search(items[i])==0)
        {
            cout<< i<< '\t'<<"Search Error in a\n";
            return 0;
        }


    for(int i=0; i<100000; i++)
        if(b.search(items[i])==0)
        {
            cout<< i<< '\t'<<"Search Error in b\n";
            return 0;
        }

    for(int i=0; i<100000; i++)
        if(c.search(items[i])==0)
        {
            cout<< i<< '\t'<<"Search Error in c\n";
            return 0;
        }
    if(a.search("Myesha")==1)
    {
        cout<<"Search failed in a"<<endl;
        return 0;
    }
    if(b.search("Myesha")==1)
    {
        cout<<"Search failed in b"<<endl;
        return 0;
    }
    if(c.search("Myesha")==1)
    {
        cout<<"Search failed in c"<<endl;
        return 0;
    }
    for(int i=0; i<items.size();i++)
    {
        a.remove(items[i]);
    } 
    
    for (int i=0; i<items.size();i++)
    {
        if (a.search(items[i])==1)
        {
            cout<<"Failed remove a"<<endl;
            return 0;
        }
    }
    for(int i=0; i<items.size();i++)
    {
        b.remove(items[i]);
    } 
    
    for (int i=0; i<items.size();i++)
    {
        if (b.search(items[i])==1)
        {
            cout<<"Failed remove b"<<endl;
            return 0;
        }
    }
    for(int i=0; i<items.size();i++)
    {
        c.remove(items[i]);
    } 
    
    for (int i=0; i<items.size();i++)
    {
        if (c.search(items[i])==1)
        {
            cout<<"Failed remove c"<<endl;
            return 0;
        }
    }

    cout<< "Successfully tested"<<endl;
}