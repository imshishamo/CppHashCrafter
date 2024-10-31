/**
 *  HashTableChained extends a Dictionary as a hash table with chaining.
 *  All objects used as keys must have a valid hashCode() method, which is
 *  used to determine which bucket of the hash table an entry is stored in.
 *  Each object's hashCode() is presumed to return an int between
 *  Integer.MIN_VALUE and Integer.MAX_VALUE.  The HashTableChained class
 *  implements only the compression function, which maps the hash code to
 *  a bucket in the table's range.
 *
 **/

#include "HashTableChained.h"
#include "String.h"
#include "Double.h"
#include "Integer.h"
#include "CheckerBoard.h"
using namespace std;
/**
 *  Construct a new empty hash table intended to hold roughly sizeEstimate
 *  entries.  (The precise number of buckets is up to you, but we recommend
 *  you use a prime number, and shoot for a load factor between 0.5 and 1.)
 **/
template<typename K, typename V>
// constructor-Estimate
HashTableChained<K, V>::HashTableChained(int sizeEstimate) {
    // Your solution here.
    tableSize = sizeEstimate;
    //cout << tableSize<< endl;
    HashTable=createHashTable(tableSize);
    /*
    if(HashTable==NULL){
        cout << "Memory allocation failed" << endl;
    }else{
        cout << "Memory allocation success" << endl;    
    }
    */
}

template<typename K, typename V>
node** HashTableChained<K, V>::createHashTable(int size){
    //cout<<size<<endl;
    node **hashTable = (node **)malloc(size * sizeof(node *));    
    for(int i=0;i<size;i++){
        hashTable[i]=NULL;
    }
    return hashTable;
}

/**
 *  Construct a new empty hash table with a default size.  Say, a prime in
 *  the neighborhood of 100.
 **/
template<typename K, typename V>
// constructor
HashTableChained<K, V>::HashTableChained() {
    // Your solution here.
}

/**
 *  Converts a hash code in the range Integer.MIN_VALUE...Integer.MAX_VALUE
 *  to a value in the range 0...(size of hash table) - 1.
 *
 *  This function should have package protection (so we can test it), and
 *  should be used by insert, find, and remove.
 **/
template<typename K, typename V>
int HashTableChained<K, V>::compFunction(int code) {
    if (code<0){
        code =-code;
    }
    return code%tableSize;
}

/**
 *  Returns the number of entries stored in the dictionary.  Entries with
 *  the same key (or even the same key and value) each still count as
 *  a separate entry.
 *  @return number of entries in the dictionary.
 **/
template<typename K, typename V>
int HashTableChained<K, V>::size() {
    int count=0;
    for(int i=0;i<tableSize;i++){
        if(HashTable[i]!=NULL){
            count++;
        }
    }
    return count;
}

/**
 *  Tests if the dictionary is empty.
 *
 *  @return true if the dictionary has no entries; false otherwise.
 **/
template<typename K, typename V>
bool HashTableChained<K, V>::isEmpty() {
    // Replace the following line with your solution.
    return true;
}

/**
 *  Create a new Entry object referencing the input key and associated value,
 *  and insert the entry into the dictionary.
 *  Multiple entries with the same key (or even the same key and
 *  value) can coexist in the dictionary.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the key by which the entry can be retrieved.
 *  @param value an arbitrary object.
 **/

template<typename K, typename V>
void HashTableChained<K, V>::insert(const K& key, const V& value) {
    int hashcode=key->hashCode();
    int index=compFunction(hashcode);
    // cout << index << endl;
    // cout<<"key : "<<key->getvalue()<<" value : "<<value->getvalue()<<" hashcode : "<<hashcode<<" index : "<<index<<endl;
    node* newNode=(node*)malloc(sizeof(node));
    newNode->value=value->getvalue();
    // 第一個 -> 是 Struct node指標型態呼叫其成員變數
    // 第二個-> 是 Integer class指標型態呼叫其成員函式
    newNode->next=NULL;
    if (HashTable[index]==NULL){
        HashTable[index]=newNode;
    }
    else
    {
        node* temp=HashTable[index];
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newNode;
    } 
}

/**
 *  Search for an entry with the specified key.  If such an entry is found,
 *  return true; otherwise return false.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the search key.
 *  @return true if an entry containing the key is found, or false if
 *          no entry contains the specified key.
 **/
template<typename K, typename V>
bool HashTableChained<K, V>::find(const K& key) {
    int hashcode=key->hashCode();
    int index=compFunction(hashcode);
    if (HashTable[index]==NULL){
        return false;
    }else
    {
        return true;
    }
}

/**
 *  Remove an entry with the specified key.  If such an entry is found,
 *  remove it from the table.
 *  If several entries have the specified key, choose one arbitrarily, then
 *  remove it.
 *
 *  This method should run in O(1) time if the number of collisions is small.
 *
 *  @param key the search key.
 */
template<typename K, typename V>
void HashTableChained<K, V>::remove(const K&  key) {
    // Replace the following line with your solution.
    int hashcode=key->hashCode();
    int index=compFunction(hashcode);
    // cout << index << endl;
    if (HashTable[index]==NULL){
        return;
    }else
    {
        node* prev=HashTable[index];
        node* curr=HashTable[index];
        while(curr!=NULL){
            node* temp=curr;
            prev->next=curr->next;
            temp->next=NULL;
            curr=curr->next;
            free(temp);
        }
        HashTable[index]=NULL;
    }
}


/**
 *  Remove all entries from the dictionary.
 */
template<typename K, typename V>
void HashTableChained<K, V>::makeEmpty() {
    // Your solution here.
    for(int i=0;i<tableSize;i++){
        if(HashTable[i]!=NULL){
            node* prev=HashTable[i];
            node* curr=HashTable[i];
            while(curr!=NULL){
                node* temp=curr;
                prev->next=curr->next;
                temp->next=NULL;
                curr=curr->next;
                free(temp);
            }
            HashTable[i]=NULL;
        }
    }
}

template<typename K, typename V>
void HashTableChained<K, V>::printCollision(){
    for(int i=0;i<tableSize;i++){
        int num=0;
        if(HashTable[i]!=NULL){
            node* curr=HashTable[i];
            while(curr!=NULL){
                num++;
                curr=curr->next;
            }
        }
        printf("%3d :",i);
        for (int i=0;i<num;i++){
            cout << "* " ;
        }
        cout << endl;
    }   
}

template class HashTableChained<String*, Integer*>;
template class HashTableChained<Double*,Integer*>;
template class HashTableChained<CheckerBoard*,Integer*>;
