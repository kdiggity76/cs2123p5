/**********************************************************************
cs2123p5.h
Purpose:
    Defines constants:
        max constants
        error constants
        Quote Result Code constants
        boolean constants
    Defines typedef for
        Token
        For the Binary Tree:
            Element
            NodeT
            TreeImp
            Tree
       For Quotes:
            QuoteSelectionItem
            QuoteSelectionImp
            QuoteSelection
            QuoteResult

 Protypes
        Functions provided by groups/individuals
        Functions provided only by groups
        Other functions provided by Larry
        Utility functions provided by Larry
Notes:

**********************************************************************/

/********* Constants *********/

// Maximum sizes
#define MAX_TOKEN_SIZE      50   // Maximum number of actual characters for a token
#define MAX_LINE_SIZE       100  // Maximum number of characters per input line
#define MAX_ID_SIZE         12   // Maximum size of an ID
#define MAX_QUOTE_ITEM      50   // Maximum number of menu items in a quote

// Boolean Constants
#define TRUE 1
#define FALSE 0

// Quote Result Code values
#define QUOTE_NORMAL        0    // Quote had no errors and is complete
#define QUOTE_PARTIAL       1    // Quote had mising options (see error for more information)
#define QUOTE_BAD_OPTION    2    // Quote had a bad option (see error for more information)
#define QUOTE_BAD_SELECTION 3    // Quote had a bad selection (see error for more information)

// Error Constants
#define ERR_ALGORITHM       903
#define ERR_COMMAND_LINE    900    // invalid command line argument
#define ERR_DATA            905    // Bad input data

// exitUsage control
#define USAGE_ONLY          0      // user only requested usage information
#define USAGE_ERR           -1     // usage error, show message and usage information

/*** typedefs ***/

typedef char Token[MAX_TOKEN_SIZE + 1];     // token type to help with parsing

// typedefs for the binary tree

// An Element can be either an Option or an Option Value
typedef struct
{
    char   cNodeType;		      // 'O' - option, 'V' - value
    char   szId[MAX_ID_SIZE + 1]; // unique ID for each node
    char   szTitle[30];           // title to display
    char   cCostInd;              // Y - it has a cost, N - it does not have a cost
    double dCost;                 // Option Value nodes have a cost
} Element;

// A node in the tree
typedef struct NodeT
{
    struct NodeT *pChild;         // For Option nodes, this points to
                                  // the first Option Value.
                                  // For Option Value nodes, this points to
                                  // an value-specific option.
    struct NodeT *pSibling;       // For Option nodes, this points to another
                                  // option within the same option value (or root).
                                  // For Option Value nodes, this points to the
                                  // next option value under the same Option.
    Element element;              // See Element above.
} NodeT;

// A TreeImp contains the root pointer for the tree.
typedef struct
{
    NodeT *pRoot;
} TreeImp;
typedef TreeImp *Tree;

// quote selection

// QuoteSelectionItem is the Option and the corresponding
// quote value (specified as a selection (from 1 to N)).
// The first option value under an option is 1.
typedef struct
{
    int    iLevel;                      // Outline level for Options:
                                        //   Level 0 is for options at
                                        //       the root level.
                                        //   Level 1 is for options subordinate
                                        //       to level 0 option values.
                                        //   Level 2 is for options subordinate
                                        //       to level 1 option values.
    char   szOptionId[MAX_ID_SIZE+1];   // Option ID  (this is not the
                                        // ID for an option value)
    int    iSelection;                  // Selection index (relative to 1)
    double  dCost;                      // Cost of this selected item
} QuoteSelectionItem;

// A Quote Selection is an array of Quote Items
typedef struct
{
    int iQuoteItemCnt;                  // Number of items in quoteItemM
    QuoteSelectionItem quoteItemM[MAX_QUOTE_ITEM];
} QuoteSelectionImp;
typedef QuoteSelectionImp *QuoteSelection;

// Quote Result
typedef struct
{
    int returnCode;             // See QUOTE result code constants
    double dTotalCost;          // Total cost (or partial cost)
    QuoteSelectionItem error;   // If returnCode is not QUOTE_NORMAL,
                                // this contains information about the
                                // quote item that caused the error.
                                // However, for QUOTE_PARTIAL, this contains
                                // information about the first missing option.
} QuoteResult;

// Prototypes of functions you must write.  Many of these functions
// require helper functions to do the real work.
NodeT *findId(NodeT *p, char szId[]);
NodeT *findParent(NodeT *pParent, NodeT *p, NodeT *pkid);
void printPriceMenu(Tree tree);
void printOne(Tree tree, char szId[]);
void freeSubTree(NodeT *p);
void freeTree(Tree tree);
void insertPriceMenu(Tree tree, Element element, char szParentId[]);
QuoteResult determineQuote(Tree tree, QuoteSelection quoteSelection);
void deleteItem(Tree tree, char szId[]);
void insertIntoSibling(NodeT **pp, Element element);

//created by Kevin
NodeT createNode(char *szID, char cType, double cost, char *szTitle);
void printNodes(NodeT *pNode);
NodeT *allocateNodeT(Element value);
void insertIntoChild(NodeT **pp, Element element);
void printQuote(NodeT *pNode, NodeT *pParent);

// Driver function to process a input data line.  Groups must write this function
void processCommand(Tree tree, QuoteSelection quote, char szInputBuffer[]);

// Some functions provided by Larry
Tree newTree();
QuoteSelection newQuoteSelection();

// Utility routines provided by Larry.  All groups will use these.
void ErrExit(int iexitRC, char szFmt[], ...);
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize);
void warning(char szFmt[], ...);
