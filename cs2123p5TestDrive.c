/******************************************************************************

    1. This file contains a simple driver and some useful functions.
    2. Project groups will create the rest of the driver in this same file.
    3. Individuals (people not on teams) will use a .o file for the rest of the driver.
    4. Quote Selections can have a maximum of MAX_QUOTE_ITEM  entries.
*******************************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

int main()
{
    Tree tree = newTree();                          // Binary tree
    char szInputBuffer[MAX_LINE_SIZE + 1];          // input text line

    Element elementA = (Element)malloc(sizeof(Element));
    Element elementB = (Element)malloc(sizeof(Element));
    Element elementC = (Element)malloc(sizeof(Element));
    Element elementD = (Element)malloc(sizeof(Element));
    Element elementE = (Element)malloc(sizeof(Element));
    Element elementF = (Element)malloc(sizeof(Element));
    Element elementG = (Element)malloc(sizeof(Element));
    Element elementH = (Element)malloc(sizeof(Element));
    Element elementI = (Element)malloc(sizeof(Element));
    Element elementJ = (Element)malloc(sizeof(Element));
    Element elementK = (Element)malloc(sizeof(Element));

    elementA.cNodeType = 'O';
    strcpy(elementA.szTitle, "Model");
    strcpy(elementA.szId, "model");

    elementB.cNodeType = 'V';
    strcpy(elementA.szId, "base");
    elementB.cCostInd = 'Y';
    elementB.dCost = 17000.00;
    strcpy(elementA.szTitle, "Base");

    elementC.cNodeType = 'V';
    strcpy(elementC.szId, "lx");
    elementC.cCostInd = 'Y';
    elementC.dCost = 19000.00;
    strcpy(elementC.szTitle, "Plus");

    elementD.cNodeType = 'O';
    strcpy(elementD.szId, "engine_base");
    strcpy(elementD.szTitle, "Engine");

    elementE.cNodeType = 'O';
    strcpy(elementE.szId, "color_base");
    strcpy(elementE.szTitle, "Color");

    elementF.cNodeType = 'O';
    strcpy(elementF.szId, "engine_LX");
    strcpy(elementF.szTitle, "Engine");

    elementG.cNodeType = 'O';
    strcpy(elementG.szId, "color_LX");
    strcpy(elementG.szTitle, "Color");

    elementH.cNodeType = 'V';
    strcpy(elementH.szId, "eng18AutBase");
    elementH.cCostInd = 'Y';
    elementH.dCost = 0.00;
    strcpy(elementH.szTitle, "1.8-liter 4 Cyl Automatic");

    elementI.cNodeType = 'V';
    strcpy(elementI.szId, "eng18ManBase");
    elementI.cCostInd = 'Y';
    elementI.dCost = 0.00;
    strcpy(elementI.szTitle, "1.8-liter 4 Cyl 6spd Manual");

    elementJ.cNodeType = 'V';
    strcpy(elementJ.szId, "whitebase");
    elementJ.cCostInd = 'Y';
    elementJ.dCost = 0.00;
    strcpy(elementJ.szTitle, "White");

    tree->pRoot->pChild->element = elementA;
    tree->pRoot->pChild->pChild->element = elementB;
    tree->pRoot->pChild->pChild->pSibling->element = elementC;
    tree->pRoot->pChild->pChild->pChild->element = elementD;
    tree->pRoot->pChild->pChild->pChild->pSibling->element = elementE;
    tree->pRoot->pChild->pChild->pSibling->pChild->element = elementF;
    tree->pRoot->pChild->pChild->pSibling->pChild->pSibling->element = elementG;
    tree->pRoot->pChild->pChild->pChild->pChild->element = elementH;
    tree->pRoot->pChild->pChild->pChild->pChild->pSibling->element = elementI;
    tree->pRoot->pChild->pChild->pChild->pSibling->pChild->element = elementJ;

    freeSubTree(tree->pRoot->pChild);


    // Free the tree, quote selection and stdin
    freeTree(tree);
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
    tree->pRoot = NULL;
    return tree;
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

