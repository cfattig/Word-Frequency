/**************************************************************************//**
*
* @file
* @brief Implementation of LinkList class
*
******************************************************************************/
#include "linklist.h"



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function creates a list by initializing headptr to nullptr.
 *
 ******************************************************************************/
LinkList::LinkList()
{
    headptr = nullptr;
}



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function walks through a given list deleting one node at a
 * time until the entire list has been freed up.
 *
 ******************************************************************************/
LinkList::~LinkList()
{
    node *temp;
    
    while ( headptr != nullptr )
    {
        temp = headptr;
        headptr = temp->next;
        delete temp;
    }
}



/***************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function added an additional node to the list. First the function
 * attempts to allocate memory for a new node. If this fails, false is retuned.
 * Next, the new node is initialized to the given word and a frequency of 1.
 * The list is traversed until the end is reached or the new node sorts into
 * the list properly. If the node is being added at the front of the list,
 * headptr is adjusted to point to the new node and the node. If not, the
 * previous node it pointed to the new one. Next, the new node is pointed to
 * the rest of the list.
 *
 * @param[in] word - word to add to the list
 *
 * @return true - the word was added to the list
 * @return false - the word was not added to the list (memory error)
 *
 ******************************************************************************/
bool LinkList::insert ( string word )
{
    node *newNode = nullptr;
    node *curr = headptr;
    node *prev = nullptr;
    


    //Attempt to create a new node
    newNode = new ( nothrow ) node;
    
    //If node couldn't be reserved
    if ( newNode == nullptr )
    {
        //Couldn't add to the list
        return false;
    }
    
    //Set contents of the new node
    newNode->frequencyCount = 1;
    newNode->word = word;
    newNode->next = nullptr;
    


    //While the current word comes after and not at the end
    while ( curr != nullptr && newNode->word > curr->word )
    {
        prev = curr;
        curr = curr->next;
    }
    
    //If adding at the start
    if ( prev == nullptr )
    {
        //Point headptr to this node
        headptr = newNode;
    }
    else
    {
        //Point the previous node to this one
        prev->next = newNode;
    }
    
    //Point this node to the rest of the list (or end)
    newNode->next = curr;
    
    //Word was added to the list successfully
    return true;
}



/***************************************************************************//**
 * @author Justin King
 *
 * @par Description:
 * This function will search through the list and if the inputted word is
 * found, removes it.  If the word appears more than once, only the first
 * instance will be removed.
 *
 * @param[in] word - word to be removed
 *
 * @return true if word is removed, false otherwise
 *
 ******************************************************************************/
bool LinkList::remove ( string word )
{
    // declare & initialize temporary pointers used to walk through list
    node *prev = headptr;
    node *curr = headptr;
    
    // check for empty list
    if ( headptr == nullptr )
    {
        return false;
    }
    
    // move pointers down as necessary
    while ( curr != nullptr && curr->word != word )
    {
        prev = curr;
        
        curr = curr->next;
    }
    
    // check to see if word was found
    if ( curr == nullptr )
    {
        return false;
    }
    
    // adjust list so chosen word drops out
    prev->next = curr->next;
    
    if ( curr == headptr )
    {
        headptr = curr->next;
    }
    
    // free memory
    delete curr;
    
    return true;
}



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function
 *
 * @param[in] word - the word that we are searching the list for
 *
 * @returns true if the word was found
 * @returns false if the word was not found
 *
 ******************************************************************************/
bool LinkList::find ( string word )
{
    node *temp;
    
    temp = headptr;
    
    while ( temp != nullptr ) //searches through the list
    {
        if ( temp->word == word ) //compares the words
        {
            return true;
        }
        
        temp = temp->next;
    }
    
    return false;
}



/***************************************************************************//**
 * @author Justin King
 *
 * @par Description:
 * This function will search for the word in the input and, if it is found,
 * increment the frequency counter for that word.
 *
 * @param[in] word - word to increment the counter for
 *
 * @return true if counter incremented, false otherwise
 *
 ******************************************************************************/
bool LinkList::incrementFrequency ( string word )
{
    // assign temporary pointer to walk through list
    node *temp = headptr;
    
    // walk through list
    while ( temp != nullptr )
    {
        // if word is found, increment counter & return true
        if ( temp->word == word )
        {
            temp->frequencyCount = temp->frequencyCount + 1;
            return true;
        }
        
        // if word is not found, move to next item in list
        temp = temp->next;
    }
    
    return false;
}



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function determines if a given list is empty or not.
 *
 * @returns true if the list is empty.
 * @returns false if the list is not empty.
 *
 ******************************************************************************/
bool LinkList::isEmpty()
{
    if ( headptr == nullptr )
    {
        return true;
    }
    else
    {
        return false;
    }
}



/***************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function finds and returns the largest frequency occuring in the list.
 * The function traverses the list linearly and compares frequencies until at
 * the end of the list. The largest frequency is returned.
 *
 * @return Maximum frequency found in the list
 *
 ******************************************************************************/
int LinkList::getMaxFrequency()
{
    node *temp = headptr;
    int max = 0;
    
    //Walk through list until at the end of the list
    while ( temp != nullptr )
    {
        //Update max if this element's frequency is greater
        if ( temp->frequencyCount > max )
        {
            max = temp->frequencyCount;
        }
        
        //Go to next element
        temp = temp->next;
    }
    
    return max;
}



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function implements a counter to increment through a given
 * list one node at a time until nullptr is reached.
 *
 * @returns the amount nodes found in the list
 *
 ******************************************************************************/
int LinkList::size()
{
    node *temp = headptr;
    int count = 0;
    
    while ( temp != nullptr )
    {
        temp = temp->next;
        count++;
    }
    
    return count;
}



/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function takes the given list and displays it to the screen
 * in decreasing word frequency count. The frequency of the given words
 * is displayed in a nicely formatted header followed by all the words
 * that had that frequency value.
 *
 * @param[out] out - where the function prints to
 *
 ******************************************************************************/
void LinkList::print ( ostream &out )
{
    node *temp = headptr;
    int max = 0; // finds highest frequency count
    bool check = false; // used for displaying frequency header
    int count = 0; // used for formatting into collumns
    
    max = getMaxFrequency();//finds highest frequency
    
    
    for ( int i = max; i > 0; i-- ) //traverses list "max" amount of times
    {
        count = 0;
        temp = headptr;
        
        while ( temp != nullptr )
        {
            if ( temp->frequencyCount == i && check == false ) //displays header
            {
                out << endl << endl << "===================================" <<
                    "============================================" << endl;
                out << "          Frequency Count: " << i << endl;
                out << "===================================" <<
                    "============================================" << endl;
                check = true;
            }
            
            if ( temp->frequencyCount == i ) //displays words
            {
                //spacing for collumns
                out << left << setw ( 35 ) << left << temp->word << left << setw ( 35 );
                count++;
                
                if ( count % 2 == 0 ) // used for inserting endline after 2 words printed
                {
                    out << endl;
                }
            }
            
            temp = temp->next;
        }
        
        check = false;
    }
    
    out << endl << endl;
    
    return;
}
