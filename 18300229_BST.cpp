// 18300229_BST - Árbol Búsqueda Binaria
# include <iostream>
# include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

//Node structure.
struct Node
{
	int nodeKey;
	struct Node* nLeft;
	struct Node* nRight;
};

Node* root;

//Class containing the activities of the tree.
class BST
{
public:
	BST() //setting root on null.
	{
		root = NULL;
	}
	void insertKey(Node*, Node*);
	void preOrderT(Node*);
	void inOrderT(Node*);
	void postOrderT(Node*);
	void showTree(Node*, int);
	void findKey(int, Node**, Node**);
	void deleteNode(int);
	void del_caseA(Node*, Node*);	//Delete a node with no children.
	void del_caseB(Node*, Node*);	//Delete a node with 1 child.
	void del_caseC(Node*, Node*);	//Delete a node with 2 children.
	void deleteNodes(Node*);
	void clearTree(Node*);
	int getDepth(Node*);
};

int main()
{
	char choice = 0;
	int	keyInput = 0;
	BST bstTrial;
	Node* inputNode = nullptr;
	do
	{
		char choice = 0;
		system("cls");
		cout << "========Binary Search Tree=========" << endl;

		do //Loop until valid input
		{
			cout << endl << "Choose an option" << endl;
			cout << "[1] Insert a new node." << endl;
			cout << "[2] Delete a node." << endl;
			cout << "[3] Display In-order traversal." << endl;
			cout << "[4] Display Pre-order traversal." << endl;
			cout << "[5] Display Post-order traversal." << endl;
			cout << "[6] Show current tree" << endl;
			cout << "[7] Calculate depth of the tree." << endl;
			cout << "[8] Delete everything in the tree." << endl;
			cout << "[9] Exit." << endl;
			cout << ">Answer: "; choice = _getch();
			system("cls");
		} while (choice < 49 or choice > 57); //ASCII from 1 to 9.

		switch (choice)
		{
		case '1':	//Insert new Node.
			cout << endl << "*** Press <Left control Key> on your last the node to finish inserting. ***" << endl;
			cout << "*** Data input will automatically stop after 100 elements." << endl << endl;
			for (int i = 0; (GetAsyncKeyState(VK_LCONTROL)) == false and i < 100; i++)
			{
				if ((GetAsyncKeyState(VK_LCONTROL)) == false)
				{
					inputNode = new Node;
					cout << "Node's value: ";
					cin >> inputNode->nodeKey;
					bstTrial.insertKey(root, inputNode);
					cout << endl;
				}
				GetAsyncKeyState; //Gets the current pressed nodeKey from the user.
			}
			break;

		case '2':	//Delete a Node
			if (root == NULL)
			{
				cout << "Tree is empty, nothing to delete" << endl;
				break;
			}
			cout << "Enter the number to be deleted : ";
			cin >> keyInput;
			bstTrial.deleteNode(keyInput);
			break;

		case '3':	//Show inOrderT
			cout << "Inorder Traversal of BST:" << endl;
			bstTrial.inOrderT(root);
			cout << endl;
			break;

		case '4':	//Show preOrderT
			cout << "Preorder Traversal of BST:" << endl;
			bstTrial.preOrderT(root);
			cout << endl;
			break;

		case '5':	//Showr postOrderT
			cout << "Postorder Traversal of BST:" << endl;
			bstTrial.postOrderT(root);
			cout << endl;
			break;

		case '6':	//prints an ugly BST
			if (root == NULL)
			{
				cout << "Tree is empty." << endl;
				break;
			}
			else
			{
				cout << "Display BST:" << endl;
				bstTrial.showTree(root, 1);
				cout << endl;
				break;
			}

		case '7':	//Calculate tree depth
			cout << "The current tree depth = ";
			cout << bstTrial.getDepth(root) << endl;
			break;

		case '8':	//Delete the whole tree
			if (root == NULL)
			{
				cout << "Tree is empty." << endl;
				break;
			}
			else
			{
				bstTrial.clearTree(root);
				cout << "Tree deleted successfully" << endl;
			}
			break;

		case '9':	//Exit program
			cout << "Thanks for using the program" << endl << endl;
			exit(1);
			break;

		default:
			break;
		}
		cout << endl;
		system("pause");
	} while (1);	//Never ending loop
}

//Inserts nodeKey (Node) to the bsTree
void BST::insertKey(Node* bsTree, Node* inputNode)
{
	if (root == NULL)
	{
		root = new Node;
		root->nodeKey = inputNode->nodeKey;
		root->nLeft = NULL;
		root->nRight = NULL;
		cout << "Root Node is Added" << endl;
		return;
	}
	if (bsTree->nodeKey > inputNode->nodeKey)
	{
		if (bsTree->nLeft != NULL)
		{
			insertKey(bsTree->nLeft, inputNode);
		}
		else
		{
			bsTree->nLeft = inputNode;
			(bsTree->nLeft)->nLeft = NULL;
			(bsTree->nLeft)->nRight = NULL;
			cout << "Node added to a left branch. <--" << endl;
			return;
		}
	}
	else
	{
		if (bsTree->nRight != NULL)
		{
			insertKey(bsTree->nRight, inputNode);
		}
		else
		{
			bsTree->nRight = inputNode;
			(bsTree->nRight)->nLeft = NULL;
			(bsTree->nRight)->nRight = NULL;
			cout << "New node added to a right branch. -->" << endl;
			return;
		}
	}
}

//Pre-order traversal (copy tree)
void BST::preOrderT(Node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		cout << ptr->nodeKey << "  ";
		preOrderT(ptr->nLeft);
		preOrderT(ptr->nRight);
	}
}
//In-order traversal (shows values from smallest to largest)
void BST::inOrderT(Node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		inOrderT(ptr->nLeft);
		cout << ptr->nodeKey << "  ";
		inOrderT(ptr->nRight);
	}
}

//Post-order (used to delete and calculate depth)
void BST::postOrderT(Node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		postOrderT(ptr->nLeft);
		postOrderT(ptr->nRight);
		cout << ptr->nodeKey << "  ";
	}
}

//displays an ugly tree
void BST::showTree(Node* ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		showTree(ptr->nRight, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root->:  ";
		else
		{
			for (i = 0; i < level; i++)
				cout << "       ";
		}
		cout << ptr->nodeKey;
		showTree(ptr->nLeft, level + 1);
	}
}

//Deleting a node with no children
void BST::del_caseA(Node* parent, Node* location)
{
	if (parent == NULL)
	{
		root = NULL;
	}
	else
	{
		if (location == parent->nLeft)
			parent->nLeft = NULL;
		else
			parent->nRight = NULL;
	}
}

//Deleting a node with one nChild
void BST::del_caseB(Node* parent, Node* location)
{
	Node* nChild;
	if (location->nLeft != NULL)
		nChild = location->nLeft;
	else
		nChild = location->nRight;
	if (parent == NULL)
	{
		root = nChild;
	}
	else
	{
		if (location == parent->nLeft)
			parent->nLeft = nChild;
		else
			parent->nRight = nChild;
	}
}

//Deleting a full node (two children)
void BST::del_caseC(Node* parent, Node* location)
{
	Node* cursorN, * tempNode, * suc, * parSuc;
	tempNode = location;
	cursorN = location->nRight;
	while (cursorN->nLeft != NULL)
	{
		tempNode = cursorN;
		cursorN = cursorN->nLeft;
	}
	suc = cursorN;
	parSuc = tempNode;
	if (suc->nLeft == NULL && suc->nRight == NULL)
		del_caseA(parSuc, suc);
	else
		del_caseB(parSuc, suc);
	if (parent == NULL)
	{
		root = suc;
	}
	else
	{
		if (location == parent->nLeft)
			parent->nLeft = suc;
		else
			parent->nRight = suc;
	}
	suc->nLeft = location->nLeft;
	suc->nRight = location->nRight;
}

//Find nodeKey's value on Node.
void BST::findKey(int key, Node** parent, Node** location)
{
	Node* cursor, * tempPtr;
	if (root == NULL)
	{
		*location = NULL;
		*parent = NULL;
		return;
	}
	if (key == root->nodeKey)
	{
		*location = root;
		*parent = NULL;
		return;
	}
	if (key < root->nodeKey)
		cursor = root->nLeft;
	else
		cursor = root->nRight;
	tempPtr = root;
	while (cursor != NULL)
	{
		if (key == cursor->nodeKey)
		{
			*location = cursor;
			*parent = tempPtr;
			return;
		}
		tempPtr = cursor;
		if (key < cursor->nodeKey)
			cursor = cursor->nLeft;
		else
			cursor = cursor->nRight;
	}
	*location = NULL;
	*parent = tempPtr;
}

//Calculates tree depth with recursion
int BST::getDepth(Node* cursor)
{
	if (cursor == NULL)	//if node to check is NULL
		return 0;

	int leftDepth = getDepth(cursor->nLeft);
	int rightDepth = getDepth(cursor->nRight);

	int max = (leftDepth > rightDepth) ?
		leftDepth
		:
		rightDepth;

	return (max + 1);
}

//Deletes and specific node in BST.
void BST::deleteNode(int item)
{
	Node* parent, * location;
	if (root == NULL)
	{
		cout << "Tree empty" << endl;
		return;
	}
	findKey(item, &parent, &location);
	if (location == NULL)
	{
		cout << "Item not present in tree" << endl;
		return;
	}
	if (location->nLeft == NULL && location->nRight == NULL)	//No children nodes.
		del_caseA(parent, location);
	if (location->nLeft != NULL && location->nRight == NULL)	//Left nChild.
		del_caseB(parent, location);
	if (location->nLeft == NULL && location->nRight != NULL)	//Right Child.
		del_caseB(parent, location);
	if (location->nLeft != NULL && location->nRight != NULL)	//Two children.
		del_caseC(parent, location);

	free(location);
	cout << "Element deleted successfully.";
}

void BST::deleteNodes(Node* nodeCursor)	//Uses post-order traversal.
{
	if (nodeCursor != NULL)
	{
		deleteNodes(nodeCursor->nLeft);
		deleteNodes(nodeCursor->nRight);
		delete nodeCursor;				//Instead of printing, deletes.
	}
}

void BST::clearTree(Node* nodeCursor)	//Deletes all nodes and then sets root to null cursor;
{
	deleteNodes(nodeCursor);
	root = nullptr;
}