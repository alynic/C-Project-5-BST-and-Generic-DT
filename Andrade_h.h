/*
	Purpose: The purpose of this program is to read, from three separate input files, the data type that is to be processed, the items
	that will be processed, and the actions associated with each of the items in the input file. After each read, and the data type
	specified for the items in the input file, the associated actions will be performed on the items in the input file. This will be
	done for three input files (one for each data type), and as the items are being processed, the binary search tree that is being
	created will be output to three separate output files(one for each data type).
*/

// Pragma directive
#pragma once

// Include statements
#include <string>
#include <fstream>
#include <iostream>

// Namespace construct
using namespace std;

// Enumerated data type for determining what action will be performed on the item associated with it
enum CommandType {DATA_TYPE, INSERT, DELETE};

// Global constants
const int MIN_INT = 1;		// Constant that indicates the minumum integer value
const int MAX_INT = 100;	// Constant that indicates the maximum integer value
const int MAX_STR = 10;		// Constant that indicates the maximum string length

// Class construct for the nodes of the binary search tree
template <class ItemType>
class TreeNode
{
	public:
	ItemType info;	// Variable to store the information inside of the pointer
	TreeNode <ItemType> *left;	// Variable to point to the left node in the binary search tree
	TreeNode <ItemType> *right;	// Variable to point to the right node in the binary search tree
};

// Class construct for construction of the binary search tree
template <class ItemType>
class TreeType
{
public:
	//	Purpose:		Class constructor
	//	Pre-condition:	None
	//	Post-condition:	Class is initialized
	TreeType();

	//	Purpose:		Class destructor
	//	Pre-condition:	Class is initialized
	//	Post-condition:	Class is destructed
	~TreeType();

	//	Purpose:		Function to check to see if the binary search tree is empty
	//	Pre-condition:	None
	//	Post-condition:	Returns a boolean value indicating whether or not the binary search tree is empty
	bool isEmpty();

	//	Purpose:		Function to check to see if the binary search tree is full
	//	Pre-condition:	None
	//	Post-condition:	Returns a boolean value indicating whether or not the binary search tree is full
	bool isFull();

	//	Purpose:		Function that will read the data from the input files
	//	Pre-condition:	Input file is opened for reading
	//	Post-condition:	The next action and item are retrieved from the input file
	void getData(ifstream& infile, ofstream& outfile, ItemType& item, char datatype, bool& complete, string& action, CommandType& command);

	//	Purpose:		Function that will construct the binary search tree
	//	Pre-condition:	Binary search tree is initialized
	//	Post-condition:	The binary search tree is built
	void buildTree(ItemType& item, bool& finished, bool& more, string& action, CommandType& command, ofstream& outfile);

	//	Purpose:		Function that inserts the item into the binary search tree
	//	Pre-condition:	Binary search tree is initialized
	//	Post-condition:	The current item is inserted into the binary search tree
	void insert(TreeNode <ItemType> *&tree, ItemType item);

	//	Purpose:		Function that checks to see if the binary search tree is full; if it is, an error message is displayed
	//	Pre-condition:	Binary search tree is initialized
	//	Post-condition:	It is determined whether or not the tree is full
	void insertItem(ItemType item, ofstream& outfile);

	//	Purpose:		Destructs the current binary search tree
	//	Pre-condition:	Binary search tree is initialized
	//	Post-condition:	The binary search tree is destructed
	void destroy(TreeNode <ItemType> *&tree);

	//	Purpose:		Searches for the indicated item for deletion from the binary search tree
	//	Pre-condition:	Binary search tree is initialized and not empty
	//	Post-condition:	The item is either found or an error message is displayed
	void deleteSearch(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile);

	//	Purpose:		Deletes the indicated item from the binary search tree
	//	Pre-condition:	Binary search tree is initialized and not empty
	//	Post-condition:	The indicated item is delete from the binary search tree
	void deleteNode(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile);

	//	Purpose:		Finds the predecessor of the node being deleted
	//	Pre-condition:	Binary search tree is initialized and not empty
	//	Post-condition:	The predecessor of the item is found
	void getPredecessor(TreeNode <ItemType> *&tree, ItemType& data);

	//	Purpose:		Deletes the predecessor so that it isn't contained in the binary search tree twice
	//	Pre-condition:	Binary search tree is initialized and not empty
	//	Post-condition:	The original location of the predecessor is deleted along with the node itself
	void deleteItem(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile);

private:
	TreeNode <ItemType> *tree;	// Binary search tree access variable
	int count;	// Control structure variable
	ItemType item;	// Variable that stores the current item being processed
};

// Function prototypes
//	Purpose:		Function converts the action retrieved from the input file into a command that can be used by the program
//	Pre-condition:	Action has a value
//	Post-condition:	Class is initialized
void convertAction(string action, CommandType& command, ifstream& infile, ofstream& outfile);

//	Purpose:		Function that prints binary search tree in pre-order notation
//	Pre-condition:	Class is initialized
//	Post-condition:	Class is initialized
template <class ItemType>
void preOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile);

//	Purpose:		Function that prints binary search tree in in-order notation
//	Pre-condition:	Class is initialized
//	Post-condition:	Class is initialized
template <class ItemType>
void inOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile);

//	Purpose:		Function that prints binary search tree in post-order notation
//	Pre-condition:	Class is initialized
//	Post-condition:	Class is initialized
template <class ItemType>
void postOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile);

// Function declarations
template <class ItemType>
TreeType <ItemType> :: TreeType()
{
	tree = NULL;
	count = 0;
}// End of TreeType() class constructor

template <class ItemType>
TreeType <ItemType> :: ~TreeType()
{
	destroy(tree);
}// End of ~TreeType() class destructor

template <class ItemType>
bool TreeType <ItemType> :: isEmpty()
{
	return tree == NULL;
}// End of isEmpty() function

template <class ItemType>
bool TreeType <ItemType> :: isFull()
{
	TreeNode <ItemType> *temp;

	try
	{
		temp = new TreeNode <ItemType>;
		delete temp;
		return false;
	}// End of try statement

	catch(std::bad_alloc exception)
	{
		return true;
	}// End of catch statement
}// End of isFull() function

template <class ItemType>
void TreeType <ItemType> :: getData(ifstream& infile, ofstream& outfile, ItemType& item, char datatype, bool& complete, string& action, CommandType& command)
{
	if (infile >> action >> item)
	{
		count++;
		outfile << "\n\n-- " << count << " --\n";
		convertAction(action, command, outfile);
	}// End of if statement

	else
		complete = true;
}// End of getData() function

template <class ItemType>
void TreeType <ItemType> :: buildTree(ItemType& item, bool& finished, bool& more, string& action, CommandType& command, ofstream& outfile)
{
	int format = 0;		// Variable to be used in and to control the in-order/pre-order/post-order operations

	switch (command)
	{
	case INSERT  :  outfile << "Insert: " << item << endl;
					insertItem(item, outfile);
					more = false;
					format = 0;
					outfile << "Pre-order:  ";
					preOrder(tree, more, format, outfile);
					format = 0;
					more = false;
					outfile << "\nIn-order:   ";
					inOrder(tree, more, format, outfile);
					more = false;
					format = 0;
					outfile << "\nPost-order: ";
					postOrder(tree, more, format, outfile);
					break;
	case DELETE  :	outfile << "Delete: " << item << endl;
					deleteItem(tree, item, outfile);
					more = false;
					format = 0;
					outfile << "Pre-order:  ";
					preOrder(tree, more, format, outfile);
					more = false;
					format = 0;
					outfile << "\nIn-order:   ";
					inOrder(tree, more, format, outfile);
					more = false;
					format = 0;
					outfile << "\nPost-order: ";
					postOrder(tree, more, format, outfile);
					break;
	}// End of switch statement
}// End of buildTree() function

template <class ItemType>
void TreeType <ItemType> :: insert(TreeNode <ItemType> *&tree, ItemType item)
{
	if (tree == NULL)
	{
		tree = new TreeNode <ItemType>;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = item;
	}// End of if statement

	else if (item < tree->info)
		insert(tree->left, item);

	else
		insert(tree->right, item);
}// End of insert() function

template <class ItemType>
void TreeType <ItemType> :: insertItem(ItemType item, ofstream& outfile)
{
	if (isFull())
		outfile << "The tree is full, no more input allowed.\n";

	else
		insert(tree, item);
}// End of insertItem() function

template <class ItemType>
void TreeType <ItemType> :: deleteSearch(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile)
{
	if (item < tree->info)
	{
		if (tree->left == NULL)
		{
			outfile << "\n" << item << " is not contained in the binary search tree\n";
			return;
		}// End of if statement

		deleteSearch(tree->left, item, outfile);
	}// End of if statement
	
	else if ( item > tree->info)
	{
		if (tree->right == NULL)
		{
			outfile << "\n" << item << " is not contained in the binary search tree\n";
			return;
		}// End of if statement

		deleteSearch(tree->right, item, outfile);
	}// End of else if statement

	else
		deleteNode(tree, item, outfile);
}// End of deleteSearch() function

template <class ItemType>
void TreeType <ItemType> :: deleteNode(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile)
{
	ItemType data;		// Variable to be used in operations deleting nodes and replacing them with their predecessor
	TreeNode <ItemType> *temp;	// Variable to be used in deleting nodes

	temp = tree;

	if (tree->left == NULL)
	{
		tree = tree->right;
		delete temp;
	}// End of if statement

	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete temp;
	}// End of else if statement

	else
	{
		getPredecessor(tree->left, data);
		tree->info = data;
		deleteSearch(tree->left, data, outfile);
	}// End of else statement
}// End of deleteNode() function

template <class ItemType>
void TreeType <ItemType> :: getPredecessor(TreeNode <ItemType> *&tree, ItemType& data)
{
	while (tree->right != NULL)
		tree = tree->right;

	data = tree->info;
}// End of getPredecessor() function

template <class ItemType>
void TreeType <ItemType> :: deleteItem(TreeNode <ItemType> *&tree, ItemType item, ofstream& outfile)
{
	deleteSearch(tree, item, outfile);
}// End of deleteItem() function

template <class ItemType>
void TreeType <ItemType> :: destroy(TreeNode <ItemType> *&tree)
{
	if (tree != NULL)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}// End of if statement
}// End of destroy() function

template <class ItemType>
void preOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile)
{
	if (tree != NULL)
	{
		if (more)
		{
			format++;
			outfile << ", ";

			if (format == 2)
			{
				outfile << "\n\t    ";
				format = 0;
			}// End of if statement

			more = false;
		}// End of if statement

		outfile << tree->info << " (";

		if (tree->left == NULL)
			outfile << "NULL, ";

		else
			outfile << tree->left << ", ";

		outfile << tree << ", ";

		if (tree->right == NULL)
			outfile << "NULL)";

		else
			outfile << tree->right << ')';

		more = true;
		preOrder(tree->left, more, format, outfile);
		preOrder(tree->right, more, format, outfile);
	}// End of if statement
}// End of preOrder() function

template <class ItemType>
void inOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile)
{
	if (tree != NULL)
	{
		inOrder(tree->left, more, format, outfile);

		if (more)
		{
			format++;
			outfile << ", ";

			if (format == 2)
			{
				outfile << "\n\t    ";
				format = 0;
			}// End of if statement

			more = false;
		}// End of if statement

		outfile << tree->info << " (";

		if (tree->left == NULL)
			outfile << "NULL, ";

		else
			outfile << tree->left << ", ";

		outfile << tree << ", ";

		if (tree->right == NULL)
			outfile << "NULL)";

		else
			outfile << tree->right << ')';

		more = true;
		
		inOrder(tree->right, more, format, outfile);
	}// End of if statement
}// End of inOrder() function

template <class ItemType>
void postOrder(TreeNode <ItemType> *&tree, bool& more, int& format, ofstream& outfile)
{
	if (tree != NULL)
	{
		postOrder(tree->left, more, format, outfile);
		postOrder(tree->right, more, format, outfile);

		if (more)
		{
			format++;
			outfile << ", ";

			if (format == 2)
			{
				outfile << "\n\t    ";
				format = 0;
			}// End of if statement

			more = false;
		}// End of if statement

		outfile << tree->info << " (";

		if (tree->left == NULL)
			outfile << "NULL, ";

		else
			outfile << tree->left << ", ";

		outfile << tree << ", ";

		if (tree->right == NULL)
			outfile << "NULL)";

		else
			outfile << tree->right << ')';

		more = true;
	}// End of if statement
}// End of postOrder() function

void convertAction(string action, CommandType& command, ofstream& outfile)
{
	if (action == "Data_Type")
		command = DATA_TYPE;

	else if (action == "Insert")
		command = INSERT;

	else if (action == "Delete")
		command = DELETE;
	
	else
	{
		outfile << "There is an error with your input";
		exit(1);
	}// End of else statement
}// End of convertAction() function
