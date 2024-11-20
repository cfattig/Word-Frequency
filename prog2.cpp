/**************************************************************************//**
 * @file
 * @brief Entry point for program 2
 *
 * @mainpage program 2 - Word Frequency
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
#include "linklist.h"



/******************************************************************************
 *                         Function Prototypes
 *****************************************************************************/
bool prepareWord ( string &word );



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
 * incremented. If during this time, an addition to the list fails, an error
 * is displayed and the function exits. The input file is closed, the list is
 * printed to the output file, and the output file is closed.
 *
 * @param[in] argc - count of arguments in argv
 * @param[in] argv - array of arguments read from the command line
 *
 * @return 0 - program ran successfully
 * @return 1 - incorrect number of arguments present
 * @return 2 - input and/or output file failed to open
 * @return 3 - memory allocation error occured while adding to the list
 *****************************************************************************/
int main ( int argc, char **argv )
{
    LinkList list;  //List used to store the words and their counts
    ifstream fin;   //Input file
    ofstream fout;  //Output file
    string temp;    //Temporary location for words from the input file
    
    
    
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
    while ( fin >> temp )
    {
        //Remove punctuation, convert to lower case; add if valid
        if ( prepareWord ( temp ) )
        {
            //Add to the list if not present, increment frequency if present
            if ( list.find ( temp ) )
            {
                list.incrementFrequency ( temp );
            }
            else
            {
                //If the list insert fails
                if ( !list.insert ( temp ) )
                {
                    //Display error message and exit
                    cout << "Memory allocation error, exiting" << endl;
                    return 3;
                }
            }
        }
    }
    
    //Done reading, close input file
    fin.close();
    
    
    
    //Print the list to the output file
    list.print ( fout );
    
    //Close output file
    fout.close();
    
    return 0;
}



/**************************************************************************//**
 * @author Nicholas Wendt
 *
 * @par Description:
 * This function removes the punctuation from the front and end of the given
 * word. The word is also converted to lower case. First, the function
 * traverses the word until the first and last non punctuation characters are
 * found. If the entire word is punctuation, false is returned. The word is
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