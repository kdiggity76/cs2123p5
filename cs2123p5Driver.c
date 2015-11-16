/******************************************************************************
cs2123p5Driver.c by Team Abacus
		    Logan Westberry
		    Kevin Chandler
		    Waylon Strosser
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
<<<<<<< HEAD
    PRINT ALL 
        prints the entire tree in a pretty print style (see sample output).
    PRINT ONE szId 
        prints one item 
    QUOTE BEGIN 
=======
<<<<<<< HEAD

    PRINT ALL
        prints the entire tree in a pretty print style (see sample output).

    PRINT ONE szId
        prints one item
    QUOTE BEGIN
=======
    PRINT ALL
        prints the entire tree in a pretty print style (see sample output).
    PRINT ONE szId
        prints one item
    QUOTE BEGIN
>>>>>>> master
>>>>>>> master
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
<<<<<<< HEAD
    DELETE szId	
        This causes the specified node to be deleted 
        from the tree.  As a result, its parent should no longer reference it.  
        It and its descendants must be freed.  Do not delete its immediate siblings.  
        For example, deleting the base should remove it from its parent's value chain, 
        but should not cause PLUS and OY to be deleted.   
=======
<<<<<<< HEAD

    DELETE szId
        This causes the specified node to be deleted
        from the tree.  As a result, its parent should no longer reference it.
        It and its descendants must be freed.  Do not delete its immediate siblings.
        For example, deleting the base should remove it from its parent's value chain,
        but should not cause PLUS and OY to be deleted.
=======
    DELETE szId
        This causes the specified node to be deleted
        from the tree.  As a result, its parent should no longer reference it.
        It and its descendants must be freed.  Do not delete its immediate siblings.
        For example, deleting the base should remove it from its parent's value chain,
        but should not cause PLUS and OY to be deleted.
>>>>>>> master
>>>>>>> master
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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
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
        //printf("%s", szInputBuffer);

        // If the line is just a comment or empty, ignore it
        if (szInputBuffer[0] == '*'  || szInputBuffer[0] == '\0')
            continue;                               // Command is a comment so skip it
	//Driver function taken from cs2123p5.h
        processCommand(tree, quoteSelection, szInputBuffer);
    }

    // Free the tree, quote selection and stdin
    freeTree(tree);
    free(quoteSelection);
    fclose(stdin);
    printf("\n");
    return 0;
}

// Driver function to process a input data line.  Groups must write this function
<<<<<<< HEAD
void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[]){
	
	//Tree node for traversing tree in functions needing a traversal pointer
	NodeT pTreeNode;
	//token type for getToken
	Token szToken;
	
	//Element type that will save data for various functions that ask for 'element'
=======
processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[]){

	//need to get parentID and szId from szInputBuffer....
	/* 	element type created for below functions requiring element (possibly to load information from
		tree/quote info into element for evaluation???)
	*/
>>>>>>> master
	Element element;
	/* Note: element consists of these traits:
		char   cNodeType;		      // 'O' - option, 'V' - value
		char   szId[MAX_ID_SIZE + 1]; // unique ID for each node
		char   szTitle[30];           // title to display
		char   cCostInd;              // Y - it has a cost, N - it does not have a cost
		double dCost;
	*/
<<<<<<< HEAD
	//stores the return code from determineQuote() for return code switch case
	int iQuoteCode;
	char *pszInput, szTempParentID[MAX_ID_SIZE + 1];
	//pszInput starts at szInputBuffer
	pszInput = szInputBuffer;
	//get first token
	pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
	//If it is a '*' then bail out of function to get next line
	if(szToken[0] = '*')
		return;

	if (strcmp(szToken, "DEFINE") == 0){
		//get next token in buffer
		pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);

		if(strcmp(szToken, "VALUE") == 0){
=======

	char *pszInput;
	//pszInput starts at szInputBuffer
	pszInput = szInputBuffer;
	//get first token
	pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);
	//If it is a '*' then bail out of function to get next line
	if(Token[0] = '*')
		return;

	if (strcmp(Token, "DEFINE") == 0){
		//get next token in buffer
		pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);

		if(strcmp(Token, "VALUE") == 0))
>>>>>>> master
			/*
				*inserts one menu item into the tree.  This is used from the DEFINE command.
				*tree inserted from Tree type at beginning of function
				*element inserted from Element type created in function
<<<<<<< HEAD
				*ParentID is given by the Input data 
			*/
			//create element traits and unique ID based on data given by the buffer
			//set cNodeType of element to V for value
			element.cNodeType = 'V';
			//next token should be the ID of the branch node/element, copied into szID
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
			memset(element.szId, '\0', sizeof(element.szId));
   			strcpy(element.szId, szToken);
			//next Token is the optionID of the parent node, copied into tempParentID
			//after tempParentID is NULL'd by memset
			//and passed to insertPriceMenu function
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE); 
			memset(szTempParentID, '\0', sizeof(szTempParentID));
   			strcpy(szTempParentID, szToken);
			
			//check that the parent ID actually exists...
			//might need to use "&element.szId, etc" instead of "element.szId"
			//findParent(NodeT *pParent, NodeT *p, NodeT *pkid);

			//next token is the cost indicator
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
			element.cCostInd = szToken[0];
			//next token is the positive or negative cost
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
			element.dCost = atof(szToken);
			//last token should be the title, string copied into element.szTitle
			memset(pszInput, '\0', sizeof(pszInput));
			strcpy(pszInput, element.szTitle); 

			//once all elements are finished, element is inserted into insertPriceMenu
			//along with the tre and Parent ID
			insertPriceMenu(tree, element, szTempParentID);

			//possibly reset all element string values to '\0' to prevent old data being passed to new nodes?f
			
		}else if(strcmp(szToken, "OPTION") == 0){
=======
			*/
+			//create element traits and unique ID based on data given by the buffer
			DEFINE VALUE szId szOptionId cCostInd dCost szTitle
			//set cNodeType of element to V for value
			element.cNodeType = 'V';
			//next token should be the ID of the branch node/element, copied into szID
			pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);
			for(i = 0; i < MAX_ID_SIZE && Token[i] != '\0'; i++){
				element.szId[i] = Token[i];
			}
			element.szId[i] = '\0';

			//next Token is the optionID of the parent node
			pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);
				//do something with optionID
			//next token is the cost indicator
			pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);
			element.cCostInd = Token[0];
			//next token is the positive or negative cost
			pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);
			element.dCost = atof(Token);
			//last token should be the title
			strcpypszInput;

			insertPriceMenu(tree, element, char szParentId[]);
		else if(strcmp(Token, "OPTION") == 0))
>>>>>>> master
			/*
				*inserts one menu item into the tree.  This is used from the DEFINE command.
				*tree inserted from Tree type at beginning of function
				*element inserted from Element type created in function
<<<<<<< HEAD
				*ParentID is given by the Input data 
			*/
			//create element traits and unique ID based on data given by the buffer
			//set cNodeType of element to O for Option
			element.cNodeType = 'O';
			//next token should be the ID of the branch node/element, copied into szID
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
			memset(element.szId, '\0', sizeof(element.szId));
   			strcpy(element.szId, szToken);
			//next Token is the ID of the parent node, which is saved to tempParentID
			//after tempParentID is NULL'd by memset
			//and passed to insertPriceMenu function
			pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE); 
			memset(szTempParentID, '\0', sizeof(szTempParentID));
   			strcpy(szTempParentID, szToken);

			//check that the parent ID actually exists...
				//find function inserted here

			//last token should be the title, string copied into element.szTitle
			memset(pszInput, '\0', sizeof(pszInput));
			strcpy(pszInput, element.szTitle); 
			//once all elements are finished, element is inserted into insertPriceMenu
			//along with the tree and Parent ID
			insertPriceMenu(tree, element, szTempParentID);
		}else
			printf("ERROR: DEFINE definition is not OPTION or VALUE...\n");

	
	}else if(strcmp(szToken, "PRINT") == 0){
		
		
		if(strcmp(szToken, "ONE") == 0){
				//get next token in buffer, which is the ID of the node to print
				pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
	                	printOne(tree, szToken);
		}else if(strcmp(szToken, "ALL") == 0)
				//entire price menu is printed
				printPriceMenu(tree);  
		else
			printf("ERROR: PRINT definition is not ONE or ALL...\n");

	}else if(strcmp(szToken, "QUOTE") == 0){
		//get next token in buffer
		pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);

		//Might move quote begin, option, and end outside of the driver function altogether...
		//Might be a loop
		/*Ex if(strcmp(Token, "QUOTE") == 0)
			//next token should be Begin			
			getToken()
			//getting next buffer line should be an QUOTE OPTION line
			fgets(szInputBuffer, MAX_LINE_SIZE, stdin)
			
			while(strcmp(Token, "END" != 0)
			{	
				
				getToken() until line is clear
				getToken()
				//get next line
				fgets(szInputBuffer, MAX_LINE_SIZE, stdin)
			}
			//when while ends with QUOTE END
			determineQuote(tree, quote);

		*/

		if (strcmp(szToken, "BEGIN") == 0){
			//do something with "BEGIN"
		}else if (strcmp(szToken, "OPTION") == 0){
			//do something with "OPTION"
		}else if(strcmp(szToken, "END") == 0){
			//take options and compile the quote
			//quote inserted from QuoteSelection at beginning of function
			//tree inserted from Tree type at beginning of function
			/*	
				* Note that the driver must examine the returnCode and print whether 
				* this was a total cost, partial cost, option 
				* error, or option selection error.  
				* For total cost and partial cost, it should also print those totals.
			*/
			iQuoteCode = determineQuote(tree, quote).returnCode;
			switch (iQuoteCode)
			{
				case QUOTE_NORMAL:
					printf("Full quote COMPLETE.\n");
					//print total cost of partial quote here
					printf("PLACEHOLDER: Print total cost here.");
				break;

				case QUOTE_PARTIAL:
					printf("Partial quote COMPLETE.\n");
					//print total cost of partial quote here
					printf("PLACEHOLDER: Print total cost here.");
					return;
				break;
				
				case QUOTE_BAD_OPTION:
					ErrExit(QUOTE_BAD_OPTION, "Option error: %d\n", iQuoteCode);
				break;

				case QUOTE_BAD_SELECTION:
					ErrExit(QUOTE_BAD_SELECTION, "Selection error: %d\n", iQuoteCode);
				break;

				default:
				printf("ERROR: Unknown error code returned by determineQuote.\n");
				ErrExit(ERR_ALGORITHM, "Unknown event type: %d\n", iQuoteCode);
			}
			

		}else
			printf("ERROR: QUOTE definition is not BEGIN, OPTION, or END...\n");

	}else if(strcmp(szToken, "DELETE") == 0){
		/* deletes one item (and its pChild children )from the tree.  
		It should not delete its siblings.  The deleted nodes
		must be freed.  This is used from the DELETE command. */
		//get next token in buffer, which is the ID of the node to delete
		pszInput = getToken(pszInput, szToken, MAX_TOKEN_SIZE);
		deleteItem(tree, szToken);
		
	//not supposed to reach this level
	}else{
		printf("Data was not read correctly, revise code for better error handling.\n");
		printf("Last token read was %s...\n", szToken);
		exit(1);
	}			
=======
			*/
			insertPriceMenu(tree, element, char szParentId[]);
		else
			printf("ERROR: DEFINE definition is not OPTION or VALUE...\n");


	}else if(strcmp(Token, "PRINT") == 0){
		//get next token in buffer
		pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);

		if(strcmp(Token, "ONE") == 0))
				//only one item is printed
	                	printOne(tree, char szId[]);
		else if(strcmp(Token, "ALL") == 0))
				//entire price menu is printed
				printPriceMenu(tree);
		else
			printf("ERROR: PRINT definition is not ONE or ALL...\n");

	}else if(strcmp(Token, "QUOTE") == 0){
		//get next token in buffer
		pszInput = getToken(pszInput, Token, MAX_TOKEN_SIZE);

		if (strcmp(Token, "BEGIN") == 0))
			//do something with "BEGIN"
		else if (strcmp(Token, "OPTION") == 0))
			//do something with "OPTION"
		else if(strcmp(Token, "END") == 0))
			//take options and compile the quote
			//quote inserted from QuoteSelection at beginning of function
			//tree inserted from Tree type at beginning of function
			/*
				* Note that the driver must examine the returnCode and print whether
				* this was a total cost, partial cost, option
				* error, or option selection error.
				* For total cost and partial cost, it should also print those totals.
			*/
			determineQuote(tree, quote);
		else
			printf("ERROR: QUOTE definition is not BEGIN, OPTION, or END...\n");

	}else if DELETE{
		/* deletes one item (and its pChild children )from the tree.
		It should not delete its siblings.  The deleted nodes
		must be freed.  This is used from the DELETE command. */
		deleteItem(tree, char szId[]);

	//not supposed to reach this level
	}else{
		printf("Data was not read correctly, revise code for better error handling.\n");
		printf("Last token read was %s...\n", Token);
		exit 1;
	}
>>>>>>> master
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
    quote->iQuoteItemCnt = 0;
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
    - Requires including <stdarg.h>
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
    - Requires including <stdarg.h>
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
<<<<<<< HEAD

<<<<<<< HEAD
    If this is an argument error (iArg >= 0), it prints a formatted message 
=======
    If this is an argument error (iArg &gt;= 0), it prints a formatted message
=======
    If this is an argument error (iArg &gt;= 0), it prints a formatted message
>>>>>>> master
>>>>>>> master
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE.
<<<<<<< HEAD

    If this is a usage error (but not specific to the argument), it prints
    the specific message and its supplemental diagnostic information.  It
    also shows the usage and exist with ERR_COMMAND_LINE.

=======
    If this is a usage error (but not specific to the argument), it prints
    the specific message and its supplemental diagnostic information.  It
    also shows the usage and exist with ERR_COMMAND_LINE.
>>>>>>> master
    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript or control:
                                    > 0 - command argument subscript
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
<<<<<<< HEAD
    if (iDelimPos > iTokenSize)
=======
    if (iDelimPos == iTokenSize)
>>>>>>> master
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

<<<<<<< HEAD
/******************** printPriceMenu *****************************
void printPriceMenu(Tree tree)
Purpose:
Print the entire tree in order format. Assigns the first node in the
tree and then send to a recursive functions. Recusive function traverses
the tree and prints all the Option nodes and thier corrisponding Option nodes.
Parameters:
I   NodeT pNode     Placeholder pointer for the root node
I   double dTotal   Tracks total cost of the order
Notes:
If empty tree is passed to the function it will do nothing.
**************************************************************************/
void printPriceMenu(Tree tree)
{
    NodeT *pNode;
    pNode = tree->pRoot;
    double dTotal = 0;
    printNodes(pNode, &dTotal);
    printf("Total\t\t\t\t\t\t%.2lf\n", dTotal);
}
/******************** findId *****************************
NodeT *findId(NodeT *p, char szId[])
Purpose:
Parameters:
Notes:
**************************************************************************/
NodeT *findId(NodeT *p, char szId[])
{
    if (p == NULL)
        return NULL;
    if (strcmp(szId, p->element.szId)==0)
        return p;
    return findId(p->pChild, szId);
    return findId(p->pSibling, szId);
}
/******************** printNodes *****************************
void printNodes(NodeT *pNode, double *dTotal)
Purpose:
Parameters:
Notes:
**************************************************************************/
void printNodes(NodeT *pNode, double *dTotal)
{
    if(pNode==NULL)
        return;
    if (pNode->element.cNodeType == 'O')
        {
            printf("%-8s\t%-26s\t%.2lf\n"
                ,pNode->element.szTitle
                ,pNode->pChild->element.szTitle
                ,pNode->pChild->element.dCost);
            *dTotal = *dTotal + pNode->pChild->element.dCost;
        }
    printNodes(pNode->pChild, dTotal);
    printNodes(pNode->pSibling, dTotal);
}
/******************** printOne *****************************
void printOne(Tree tree, char szId[])
Purpose:
Prints one item from the tree.
This is used from the PRINT ONE command.
Parameters:
I   NodeT pNode     Assigned as pointer node to the result if the findID function
I   char szID       Passed value used to find desired node in tree
Notes:
If node is not found the function will print nothing.
**************************************************************************/
void printOne(Tree tree, char szId[])
{
    NodeT *pNode;
    pNode = tree->pRoot;
    pNode = findId(pNode, szId);
        if(pNode != NULL)
        {
            printf("%-8s\t%-26s\t%.2lf\n"
                    ,pNode->element.szTitle
                    ,pNode->element.szTitle
                    ,pNode->element.dCost);
        }
}
/******************** freeSubTree *****************************
void freeSubTree(NodeT *p)
Purpose:
Deallocates the memory for the node and all of its subnodes.
Parameters:
I   NodeT p     Starting node to be freed
Notes:
**************************************************************************/
void freeSubTree(NodeT *p)
{
    //do nothing if passed a non-existant node
    if (p == NULL)
        return;
    //free child and sibling nodes starting from passed node
    freeSubTree(p->pSibling);
    freeSubTree(p->pChild);
    free (p);
}
/******************** freeTree *****************************
void freeTree(Tree tree)
Purpose:
Deallocate the tree memory and all of its nodes using freeSubTree to
deallocate the nodes.
Parameters:
Notes:
**************************************************************************/
void freeTree(Tree tree)
{
    //do nothing if passed a non-existant tree
    if (tree == NULL)
        return;
    //deallocates all nodes
    freeSubTree(tree->pRoot);
    free (tree);
}
=======
>>>>>>> master
