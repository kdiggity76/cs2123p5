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
void insert(Tree *tree, NodeT *item);

int main()
{
    Tree ptree = newTree();                          // Binary tree

    NodeT pModel = createNode("model", 'O', 0.00, "Model");
    NodeT pBase = createNode("base", 'V', 12000.00, "Base");
    NodeT pBEingine = createNode("engine_base", 'O', 0.00, "Engine");
    NodeT pB18Eng = createNode("eng18AutBase", 'V', 0.00, "1.8-liter 4 Cyl Automatic");
    NodeT pBColor = createNode("color_base", 'O', 0.00, "Color");
    NodeT pBColorBlue = createNode("bluebase", 'V', 50.00, "Blue");
    NodeT pBAudio = createNode("audio_base", 'O', 0.00, "audio");
    NodeT pBAudioStd = createNode("audioStdBase", 'V', 0.00, "Audio Std");
    NodeT pWarrenty = createNode("warrenty", 'O', 0.00, "Warrenty");
    NodeT pWarrenty1 = createNode("warrenty1", 'V', 500.00, "40k/3yr");


    ptree->pRoot = &pModel;
    pModel.pChild = &pBase;
    pBase.pChild = &pBEingine;
    pBEingine.pChild = &pB18Eng;
    pBEingine.pSibling = &pBColor;
    pBColor.pChild = &pBColorBlue;
    pBEingine.pSibling = &pBAudio;
    pBAudio.pChild = &pBAudioStd;
    pModel.pSibling = &pWarrenty;
    pWarrenty.pChild = &pWarrenty1;

    printPriceMenu(ptree);

    freeSubTree(ptree->pRoot->pChild);

    printPriceMenu(ptree);

    // Free the tree, quote selection and stdin
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

NodeT createNode(char *szID, char cType, double cost, char *szTitle)
{
	NodeT* node = malloc(sizeof(NodeT));
	strcpy(node->element.szId, szID);
	strcpy(node->element.szTitle, szTitle);
	node->element.cNodeType = cType;
	node->element.dCost = cost;
	if (cType == 'V')
		node->element.cCostInd = 'Y';
	return *node;
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

