/**************************************************************************//**
 * @file
 * @brief Entry point for the STL list version of the program
 *
 * @mainpage program 2 - Word Frequency (STL)
 *
 * @section course_section Course Information
 *
 * @author Christian Fattig, Justin King, Nicholas Wendt
 *
 * @date Oct 28, 2016
 *
 * @par Professor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250 - M001 -  1:00-pm
 *
 * @par Location:
 *         CB - 107
 *
 * @section program_section Program Information
 *
 * @details
 * This program will sort the words in a text file based on the number of
 * occurences.  Words occuring the same number of times will be sorted
 * alphabetically.
 *
 * The text file will be read in one word at a time.  As each word is read
 * in, any punctuation will be removed from the beginning and the end and
 * the word will be converted to lowercase.  If it is the first occurence
 * of the word, it will be added to the list.  If the word is already in
 * the list, the frequency count will be incremented.
 *
 * Once all of the words are read in and counted, the results will be written
 * to another text file.
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 @verbatim
 c:\> prog2.exe input.txt output.txt
 input.txt - text file to be read from
 output.txt - text file to be written to
 @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 *
 * @par Modifications and Development Timeline:
 <a href="https://gitlab.mcs.sdsmt.edu/CSC250fa16p2/team01.git">
 * Please see the git repository</a>
 *
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <list>
#include <algorithm>

using namespace std;



/*!
* @brief Used to store the contents of an element in the list
*/
struct item
{
    int frequencyCount; /*!< Number of times the word occurs */
    string word;        /*!< The word for this element */
    
    bool operator== ( const item &other ); /*!< Needed for the find function */
};



/******************************************************************************
 *                         Function Prototypes
 *****************************************************************************/
bool compare2Items ( item &l, item &r );
bool prepareWord ( string &word );
void printList ( ostream &out, list<item> list );



/**************************************************************************//**
 * @authors Nicholas Wendt, Christian Fattig
 *
 * @par Description:
 * This is the starting point for the program. First, the number of arguments
 * is verified; an error message and usage statement are displayed if
 * incorrect and the funcion exits. Next, the function attempts to open the
 * input and output files. If either file failed to open, an error message is
 * displayed and the function exits. Each word is then read from the input
 * file, processed and added to the list if new they are not exclusively
 * punctuation characters. If already in the list, the frequency is
 * incremented. The input file is closed, the list is sorted and printed to the
 * output file, and the output file is closed.
 *
 * @param[in] argc - count of arguments in argv
 * @param[in] argv - array of arguments read from the command line
 *
 * @return 0 - program ran successfully
 * @return 1 - incorrect number of arguments present
 * @return 2 - input and/or output file failed to open
 *****************************************************************************/
int main ( int argc, char **argv )
{
    list<item> list;    //List used to store the words and their counts
    std::list<item>::iterator it;   //Iterator for the item list
    ifstream fin;       //Input file
    ofstream fout;      //Output file
    item temp;          //Temporary location for words from the input file



    //If argument count is not 3
    if ( argc != 3 )
    {
        //Display error and usage statement
        cout << "Error, invalid number of arguments!" << endl;
        cout << "Usage: C:\\> prog2.exe  shortstory.txt  results.txt" << endl;
        return 1;
    }
    


    //Attempt to open the input and output files
    fin.open ( argv[1] );
    fout.open ( argv[2] );
    
    //Verify success
    if ( !fin || !fout )
    {
        //Display error message
        cout << "Error, one or more files did not open!" << endl;
        
        //Close the files (one may have opened)
        fin.close();
        fout.close();
        return 2;
    }
    


    //Read until end of file
    while ( fin >> temp.word )
    {
        //Remove punctuation, convert to lower case; add if valid
        if ( prepareWord ( temp.word ) )
        {
            //Linear search until end is reached or word is found
            it = find ( list.begin(), list.end(), temp );
            
            //Add to the list if not present, increment frequency if present
            if ( it != list.end() )
            {
                it->frequencyCount++;
            }
            else
            {
                //Set initial frequency
                temp.frequencyCount = 1;
                
                //Add to the end of the list (find is linear anyways)
                list.insert ( it, temp );
            }
        }
    }
    
    //Done reading, close input file
    fin.close();
    


    //Sort by frequency first, then alphabetically in each frequency group
    list.sort ( compare2Items );
    
    //Print the list to the output file
    printList ( fout, list );
    
    //Close output file
    fout.close();
    
    return 0;
}


/**************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function is used to compare two items with the == operator. Items are
 * equivalent if their words are the same. (This is required to use the
 * algorithm find function)
 *
 * @param[in] other - item being compared
 *
 * @returns true - the items are equivalent
 * @returns false - the items are not equivalent
 *
 *****************************************************************************/
bool item::operator== ( const item &other )
{
    //Items are as equal as their words
    return word == other.word;
}



/**************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function is used to compare two items while sorting. First, the
 * frequencies are compared such that the items will be sorted in descending
 * order by frequency. If the frequencies are the same, the words are compared
 * to sort the items alphabetically within their frequency sorting groups.
 *
 * @param[in] l - left item for the comparison
 * @param[in] r - right item for the comparison
 *
 * @returns true - the left item is first
 * @returns false - the right item is first
 *
 *****************************************************************************/
bool compare2Items ( item &l, item &r )
{   
    //If frequency is the same
    if ( l.frequencyCount == r.frequencyCount )
    {
        //If left word comes first
        if ( l.word < r.word )
        {
            //Left item is first
            return true;
        }
        
        //Right item is first
        return false;
    }
    
    //If left item is more frequent than right item
    if ( l.frequencyCount > r.frequencyCount )
    {
        //Left item is first
        return true;
    }
    
    //Right item is first
    return false;
}



/**************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function removes the punctuation from the front and end of the given
 * word. The word is also converted to lower case. First, the function
 * traverses the word until the first and last non punctuation characters are
 * found. If the entire word is punctuation, false is returned. The word's
 * punctuation is removed and the word is converted to lower case.
 *
 * @param[in,out] word - word to be processed
 *
 * @returns true - the word is valid (should be added to the list)
 * @returns false - the word is all punctuation
 *
 *****************************************************************************/
bool prepareWord ( string &word )
{
    int i = 0;                      //Start on first character
    int end = word.length() - 1;    //End on last character
    


    //Find first non punct character
    while ( i < end && ispunct ( ( unsigned char ) word[i] ) )
    {
        i++;
    }
    
    //Find last non punct character
    while ( end > -1 && ispunct ( ( unsigned char ) word[end] ) )
    {
        end--;
    }
    
    //If whole word was punct
    if ( i > end )
    {
        //Whole word was punct
        return false;
    }
    


    //Get substring without punct
    word = word.substr ( i, end + 1 - i );
    
    //Convert to lower case
    for ( i = 0; i < ( int ) word.length(); i++ )
    {
        word[i] = tolower ( word[i] );
    }
    
    //Word is good
    return true;
}



/**************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function prints the contents of a sorted list to the given output
 * stream. The list is traversed and a frequency header is printed when
 * a new frequency is found. The list's words are printed in two columns in
 * each frequency group in alphabetical order.
 *
 * @param[in]       list - pre-sorted list to be printed
 * @param[in,out]   out - output stream to print the list to
 *
 *****************************************************************************/
void printList ( ostream &out, list<item> list )
{
    int frequency = 0;      //Current frequency "group"
    bool column = false;    //If the word should be printed in the left column
    


    //Traverse the list
    for(auto x : list)
    {
        //If frequency changes
        if ( frequency != x.frequencyCount )
        {
            //Update frequency
            frequency = x.frequencyCount;
            
            //Display a new frequency header
            out << "\n\n" << left;
            out << setfill ( '=' ) << setw ( 79 ) << "" << setfill ( ' ' );
            out << setw ( 11 ) << "\n" << "Frequency Count: " << frequency;
            out << endl;
            out << setfill ( '=' ) << setw ( 79 ) << "" << setfill ( ' ' );
            
            //Reset columns for the new group
            column = false;
        }
        


        //Alternate columns
        if ( !column )
        {
            out << endl << setw ( 35 ) << x.word;
        }
        else
        {
            out << x.word;
        }
        
        //Toggle column
        column = column ? false : true;
    }
}