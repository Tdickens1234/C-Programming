#include "/home/cs340/progs/17f/p9/hTable.h"

//default constructor sets the table size for the hash table

HT::HT(const unsigned& hs)
{
    hsize = hs;
    hTable.resize(hs);
}

//destructor first frees memory of the list containers, then the vector containers for the hash and pointer tables

HT::~HT()
{

for(unsigned i = 0; i < hTable.size(); i++)
{
    hTable[i].erase( hTable[i].begin(), hTable[i].end());
}
    hTable.erase(hTable.begin(), hTable.end());
    pTable.erase(pTable.begin(), pTable.end());
}

//insert function inserts entry into hash table, and address of entry in hash table into the pointer table

void HT::insert(const Entry& e)
{
    int i = hash(e.key);
    list<Entry>& l = hTable[i];
    auto found = find_if(l.begin(), l.end(), [e](const Entry& e2){return e2.key == e.key;}); //lambda captures the key and compares it to find the position of the entry if it already exists in the table
    if( found == l.cend())
    {
        cout << " Entry = " << i << endl;
        auto itemPointer = l.insert(l.begin(), e);
        pTable.push_back(&*itemPointer);
    }
    else
    {
        cout << " Key already exists in Table!" << endl;
    }
}

//search function searches through the table to find the entry and prints appropriate message

void HT::search(const string& key)
{
    int i = hash(key);
    list<Entry> l = hTable[i];
    auto found = find_if(l.begin(), l.end(), [key](const Entry& e3){return e3.key == key;}); //lambda uses logic from insert function
    if(found == l.cend())
    {
        cout << " Key not found!" << endl;
    }
    else
    {
        cout << "==> Number:" << setw(6) << right << found->num << " - item: " << found->desc << endl;
    }
}

//prints the active values of the hTable and ignores empty values

void HT::hTable_print()
{

int endlCounter = 0;
for(unsigned i = 0; i < hTable.size(); i++)
{
    endlCounter++;
    if(!hTable[i].empty())
    {
        endlCounter = i;
        for( auto j = hTable[i].begin(); j != hTable[i].end(); j++)
        {
            cout << endl << setw(5) << right << i << setw(1) << ":" << setw(4) << j->key << " - " << setw(5) << right << j->num << " - " << j->desc;
        }
    }
    else
    {
        endlCounter++;
        if( endlCounter - i == 1) {cout << endl;}
    }
}
cout << endl;
}

//compare function used for the unary object to sort the pointer table

bool cmp(Entry* p, Entry* q)
{
    int compared = p->key.compare(0, 3, q->key);
    if( compared < 0 ) { return true;}
    else { return false;}
}

//sorts and prints all the values in the pointer table

void HT::pTable_print()
{

sort(pTable.begin(), pTable.end(), cmp);
cout << endl;
for(unsigned i = 0; i < pTable.size(); i++)
{
    cout << setw(6) << right << pTable[i]->key << " - " << setw(4) << right << pTable[i]->num << " - " <<  pTable[i]->desc << endl;
}
}
