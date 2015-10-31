/******************************************************************************
cs2123p5Driver.c by Larry Clark  (For groups, place group name here and
list your names.  For individuals, you will not be changing this.
Purpose:
    This program manages a Price Menu for the Klunker Car Company  using a
    binary tree to represent the information.  It uses input commands to 
    manage the tree, print its contents, and print a quote.
Command Parameters:
    n/a
Input:
    DEFINE OPTION szId szSubordinateToId szTitle
        where szId is the ID of this new node,
              szSubordinateToId is the ID of the node that is its 
                  parent (via a pChild pointer),
              szTitle is the title for this option (e.g., "Model").  
        Assuming the node with szSubordinateToId exists, this inserts a 
        new node in the tree.  If a child already exists, follow that child's 
        sibling chain until you can insert it at a pointer that would be NULL.
        Note:  if we are inserting at the root, the szSubordinateToId will be "ROOT".
        Print warnings (don't terminate) if the szId already exists or if the
        szSubordinateToId doesn't exist.

    DEFINE VALUE szId szOptionId cCostInd dCost szTitle
        where szId is the ID of this new node,
              szOptionId is the ID of the option which is its parent 
                         (via a pChild pointer),
              cCostInd is a character (not a string) representing whether it has a cost,
              dCost is the cost which may be positive or negative,
              szTitle is the title for this option value (e.g., "Racing White").
        Assuming the option node with szOptionId exists, this inserts a new node 
        in the tree.  If a child already exists for that Option, follow that child's 
        sibling chain until you can insert it at a pointer that would be NULL.
        Print warnings (don't terminate) if the szId already exists or if the 
        szOptionId doesn't exist.  If the node containing the szOptionId isn't 
        an OPTION, print a warning.

    PRINT ALL 
        prints the entire tree in a pretty print style (see sample output).

    PRINT ONE szId 
        prints one item 
    QUOTE BEGIN 
        starts a quote selection.  determineQuote isn't called.
    QUOTE OPTION iLevel szOptionId iSelection
    …
    QUOTE END
        invokes determineQUote passing the quote selction information.
        Example:
        QUOTE BEGIN
        QUOTE OPTION 0 MODEL 1	// selected BASE
        QUOTE OPTION 1 ENGINE_BASE 1	// selected 1.8-liter 4 Cyl Automatic
        QUOTE OPTION 1 COLOR_BASE 2	// selected BLUE
        QUOTE OPTION 1 AUDIO_BASE 2	// selected 8-TRK
        QUOTE OPTION 0 WARRANTY 3	// selected 70k/5yr 
        QUOTE END
        It would print a quote:
        MODEL     BASE				        17000
        ENGINE    1.8-liter 4 Cyl Automatic 	0
        COLOR     Blue                         50
        AUDIO     8-Track                    -100
        WARRANTY  70k/5yr                     900
        Total                               17850

    DELETE szId	
        This causes the specified node to be deleted 
        from the tree.  As a result, its parent should no longer reference it.  
        It and its descendants must be freed.  Do not delete its immediate siblings.  
        For example, deleting the base should remove it from its parent's value chain, 
        but should not cause PLUS and OY to be deleted.   
        Print a warning if the szId doesn't already exist.

    *	a comment in the data.  It is only used to explain the data.

Results:
    The commands cause a binary tree to be modified, printed or used to get 
    a prie quote.
    Each command is also printed by this simple driver.
Returns:
    0 - normal
    ??
Notes:
    1. This file contains a simple driver and some useful functions. 
    2. Project groups will create the rest of the driver in this same file.
    3. Individuals (people not on teams) will use a .o file for the rest of the driver.
    4. Quote Selections can have a maximum of MAX_QUOTE_ITEM  entries.
*******************************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#include &lt;stdarg.h&gt;
#include &lt;stdlib.h&gt;
#include "cs2123p5.h"

int main()
{
    Tree tree = newTree();                          // Binary tree
    char szInputBuffer[MAX_LINE_SIZE + 1];          // input text line

    // Variables for Quote
    QuoteSelection quoteSelection = newQuoteSelection();

    // Read command lines until EOF
    while (fgets(szInputBuffer, MAX_LINE_SIZE, stdin) != NULL)
    {
        printf("%s", szInputBuffer);

        // If the line is just a comment or empty, ignore it
        if (szInputBuffer[0] == '*'  || szInputBuffer[0] == '\0')
            continue;                               // Command is a comment so skip it

        processCommand(tree, quoteSelection, szInputBuffer);
    }

    // Free the tree, quote selection and stdin
    freeTree(tree);
    free(quoteSelection);
    fclose(stdin);
    printf("\n");
    return 0;
}
/******************** newTree **************************************
  Tree newTree()
Purpose:
    Allocates memory for a TreeImp and initializes it.
Parameters:
    n/a
Notes:
    - Checks for malloc memory allocation error. 
Returns:
    Returns a Tree.  Note that a Tree is simply a pointer to 
    a TreeImp. 
**************************************************************************/
Tree newTree()
{
    Tree tree = (Tree)malloc(sizeof(TreeImp));
    if (tree == NULL)
        ErrExit(ERR_ALGORITHM, "malloc allocation error for TreeImp");
    tree-&gt;pRoot = NULL;
    return tree;
}
/******************** newQuoteSelection **************************************
  QuoteSelection newQuoteSelection()
Purpose:
    Allocates memory for a QuoteSelectionImp and initializes it.
Parameters:
    n/a
Notes:
    - Checks for malloc memory allocation error. 
Returns:
    Returns a QuoteSelection.  Note that a QuoteSelection is simply a pointer to 
    a QuoteSelectionImp. 
**************************************************************************/
QuoteSelection newQuoteSelection()
{
    QuoteSelection  quote= (QuoteSelection)malloc(sizeof(QuoteSelectionImp));
    if (quote == NULL)
        ErrExit(ERR_ALGORITHM, "malloc allocation error for QuoteSelectionImp");
    quote-&gt;iQuoteItemCnt = 0;
    return quote;
}

/***  U T I L I T Y functions ***/

/******************** ErrExit **************************************
  void ErrExit(int iexitRC, char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program with the specified exit return code.
Parameters:
    I   int iexitRC             Exit return code for the program
    I   char szFmt[]            This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Notes:
    - Prints "ERROR: " followed by the formatted error message specified 
      in szFmt. 
    - Prints the file path and file name of the program having the error.
      This is the file that contains this routine.
    - Requires including &lt;stdarg.h&gt;
Returns:
    Returns a program exit return code:  the value of iexitRC.
**************************************************************************/
void ErrExit(int iexitRC, char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n");
    exit(iexitRC);
}
/******************** warning **************************************
  void warning(char szFmt[], ... )
Purpose:
    Prints an warning message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
Parameters:
    I   char szFmt[]            This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Notes:
    - Prints "Warning: " followed by the formatted warning message specified 
      in szFmt. 
    - Usually after using the warning function, your code should return.
    - Requires including &lt;stdarg.h&gt;
Returns:
    n/a
**************************************************************************/
void warning(char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("Warning: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n");
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    In general, this routine optionally prints error messages and diagnostics.
    It also prints usage information.

    If this is an argument error (iArg &gt;= 0), it prints a formatted message 
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits 
    with ERR_COMMAND_LINE.

    If this is a usage error (but not specific to the argument), it prints 
    the specific message and its supplemental diagnostic information.  It 
    also shows the usage and exist with ERR_COMMAND_LINE. 

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript or control:
                                    &gt; 0 - command argument subscript
                                    0 - USAGE_ONLY - show usage only
                                    -1 - USAGE_ERR - show message and usage
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    switch (iArg)
    {
        case USAGE_ERR:
            fprintf(stderr, "Error: %s %s\n"
                , pszMessage
                , pszDiagnosticInfo);
            break;
        case USAGE_ONLY:
            break;
        default:
            fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
                , iArg
                , pszMessage
                , pszDiagnosticInfo);
    }
    // print the usage information for any type of command line error
    fprintf(stderr, "p5 \n");
    if (iArg == USAGE_ONLY)
        exit(USAGE_ONLY); 
    else 
        exit(ERR_COMMAND_LINE);
}

/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
    Examines the input text to return the next token.  It also
    returns the position in the text after that token.  This function
    does not skip over white space, but it assumes the input uses 
    spaces to separate tokens.
Parameters:
    I   char *pszInputTxt       input buffer to be parsed
    O   char szToken[]          Returned token.
    I   int iTokenSize          The size of the token variable.  This is used
                                to prevent overwriting memory.  The size
                                should be the memory size minus 1 (for
                                the zero byte).
Returns:
    Functionally:
        Pointer to the next character following the delimiter after the token.
        NULL - no token found.
    szToken parm - the returned token.  If not found, it will be an
        empty string.
Notes:
    - If the token is larger than the szToken parm, we return a truncated value.
    - If a token isn't found, szToken is set to an empty string
    - This function does not skip over white space occurring prior to the token.
**************************************************************************/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize)
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    char szDelims[20] = " \n\r";        // delimiters
    szToken[0] = '\0';

    // check for NULL pointer 
    if (pszInputTxt == NULL)
        ErrExit(ERR_ALGORITHM
        , "getToken passed a NULL pointer");

    // Check for no token if at zero byte
    if (*pszInputTxt == '\0')
        return NULL;

    // get the position of the first delim
    iDelimPos = strcspn(pszInputTxt, szDelims);

    // if the delim position is at the first character, return no token.
    if (iDelimPos == 0)
        return NULL;

    // see if we have more characters than target token, if so, trunc
    if (iDelimPos &gt; iTokenSize)
        iCopy = iTokenSize;             // truncated size
    else
        iCopy = iDelimPos;

    // copy the token into the target token variable
    memcpy(szToken, pszInputTxt, iCopy);
    szToken[iCopy] = '\0';              // null terminate

    // advance the position
    pszInputTxt += iDelimPos;
    if (*pszInputTxt == '\0')
        return pszInputTxt;
    else
        return pszInputTxt + 1;
}
</pre></body></html>
