/**************************************************************************//**
*
* @file
* @brief Definition of LinkList class
*
******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

#ifndef __LINKLIST_H
#define __LINKLIST_H

/*!
 * @brief allows entry of words into list sorted alphabetically with
 * frequency counter
 */
class LinkList
{
    public:
        LinkList();
        ~LinkList();
        
        bool insert ( string word );
        bool remove ( string word );
        bool find ( string word );
        bool incrementFrequency ( string word );
        bool isEmpty();
        int getMaxFrequency();
        int size();
        void print ( ostream &out );
        
    private:
        /*!
        * @brief Used to store the contents of an element in the list
        */
        struct node
        {
            int frequencyCount; /*!< Number of times the word occurs */
            string word;        /*!< The word for this element */
            node *next;         /*!< Pointer to the next list item */
        };
        node *headptr;          /*!< Pointer to beginnig of list */
};

#endif