// SortedStringList.cpp  -- Implementation file for ADT SortedList (Pointer-based implementation)
// Revised 2019-02-14


#include "SortedStringList.h"
#include <iostream>
#include <exception>

using namespace std;

// Constructor

SortedStringList::SortedStringList()
{
    header = new DListNode;
    trailer = new DListNode;
    header->prev = NULL;
    header->next = trailer;
    trailer->prev = header;
    trailer->next = NULL;
    numItems = 0;
    header->item = "!!-Header node";
    trailer->item = "~~-Trailer node";
} // end (Default) Constructor

// List Operations:

bool SortedStringList::isEmpty() const
// Returns true is the list is empty
{
    return bool(size() == 0);
} // end isEmpty


int SortedStringList::size() const
// Returns the number of items in the list
{
    return numItems;
} // end size


void SortedStringList::add(ListItemType newItem)
//                         IN
// Inserts newItem into its proper position in a sorted list.
{
    // use locateIndex to find the index of where newItem should go
    
    // use find to return a pointer to the proper insertion point
    
    // update the size of the list
    
    // pointer p points to a node which item is the newItem
    DListNode *p = new DListNode;
    p->item = newItem;
    int index;
    if(numItems == 0) // add first item
    {
        p->prev = header;
        p->next = trailer;
        header->next = p;
        trailer->prev = p;
    }
    else
    {
        index = locateIndex(newItem);
        DListNode *precurr;  // this is a pointer points to the previous of the pointer which has the newItem
        if(index == 1)
        {
            precurr = header;
        }
        else
        {
            precurr = find(index - 1);
        }
        p->prev = precurr;
        p->next = precurr->next;
        precurr->next->prev = p;
        precurr->next = p;
    }
    ++numItems;
} // end insert


void SortedStringList::remove(int index)
//                            IN
// Removes the item at position index of a sorted list,
//      if 1 <= index <= size(); otherwise, throws an exception

{
    if ((index>=1) && (index<=size()))
    {
        
        // use find to return a pointer to node to delete
        
        // update the pointers and delete the node
        
        // update the size of the list
        
        DListNode *p = new DListNode;
        p = find(index);
        p->next->prev = p->prev;
        p->prev->next = p->next;
        // return p to the system
        delete p;
        p = NULL;
        --numItems;
    }
    else
        throw "Bad index or List empty on remove()";
} // end remove

void SortedStringList::get(int index, ListItemType& dataItem) const
//                         IN         OUT
// Retrieves the item at position index of a sorted list,
// if 1 <= index <= size(); otherwise, throws an exception

{
    
    if ((index>=1) && (index<=size()))
    {
        // use find to return a pointer to the node
        DListNode *p = new DListNode;
        p = find(index);
        dataItem = p->item;
    }
    else
        throw "Bad index or List empty on get()";
} // end get

void SortedStringList::removeAll()
// Removes all the items in the list.
{
    // iterate through the list, removing the items one at a time
    DListNode *p = new DListNode;
    while(numItems != 0)
    {
        p = trailer->prev;
        p->prev->next = trailer;
        trailer->prev = p->prev;
        delete p;
        p = NULL;
        --numItems;
    }
    
} // end remove

int SortedStringList::locateIndex(ListItemType item)    const
// Returns the position where the item belongs or exists in a sorted list.
{
    
    DListNode *nodePtr = header;
    int index = 0;
    do
    {
        nodePtr = nodePtr->next;
        index++;
    }     while( nodePtr != trailer && (item.compare(nodePtr->item) > 0));
    return index;
    
} // end locateIndex

// Private function:

SortedStringList::DListNode *SortedStringList::find(int index)const
{
    // This function returns a pointer to the node at the referenced index.
    // If used in an insertion, the pointer is to the node which will become the successor.
    DListNode *nodePtr;
    
    if (index >= 1 && index <= size()+1)
    {
        nodePtr = header->next;
        for (int i=1; i < index; i++)
        {
            nodePtr = nodePtr->next;
        }
        return nodePtr;
    }
    else
    {
        throw "not found";
    }
} // end find

// This function is not in the specifications, but you may find it useful for debugging purposes.
void SortedStringList::display() const
{
    DListNode *p = header;
    while (p != NULL)
    {
        cout << p->item << endl;
        p = p->next;
    }
}

// End of implementation file.
