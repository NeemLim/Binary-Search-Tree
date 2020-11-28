// 18300229_BST - Arbol Busqueda Binaria
# include <iostream>
# include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

/*
 * Class Declaration
 */

struct node
{
	int key;
	struct node* left;
	struct node* right;
};

node* root;

class BST
{
public:

	void find(int, node**, node**);
	void insert(node*, node*);
	void del(int);
	void case_a(node*, node*);
	void case_b(node*, node*);
	void case_c(node*, node*);
	void preorder(node*);
	void inorder(node*);
	void postorder(node*);
	void display(node*, int);
	void eraseAll(node*);
	BST()
	{
		root = NULL;
	}
};
/*
 * Main Contains Menu
 */
int main()
{
	char choice = 0;
	int	keyInput = 0;
	BST bstTrial;
	node* inputNode = nullptr;
	do
	{
		char choice = 0;
		system("cls");
		cout << "========Binary Search Tree=========" << endl;

		do //Loop until correct input
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
		case '1':	//Insert new node.
			cout << endl << "*** Press <Left control Key> on your last the node to finish inserting. ***" << endl;
			cout << "*** Data input will automatically stop after 100 elements." << endl << endl;
			for (int i = 0; (GetAsyncKeyState(VK_LCONTROL)) == false and i < 100; i++)
			{
				if ((GetAsyncKeyState(VK_LCONTROL)) == false)
				{
					inputNode = new node;
					cout << "Node: ";
					cin >> inputNode->key;
					bstTrial.insert(root, inputNode);
				}
				GetAsyncKeyState; //Gets the current pressed key from the user.
			}
			break;

		case '2':	//Delete a node
			if (root == NULL)
			{
				cout << "Tree is empty, nothing to delete" << endl;
				break;
			}
			cout << "Enter the number to be deleted : ";
			cin >> keyInput;
			bstTrial.del(keyInput);
			break;

		case '3':	//Show inorder
			cout << "Inorder Traversal of BST:" << endl;
			bstTrial.inorder(root);
			cout << endl;
			break;

		case '4':	//Show preorder
			cout << "Preorder Traversal of BST:" << endl;
			bstTrial.preorder(root);
			cout << endl;
			break;

		case '5':	//Showr postorder
			cout << "Postorder Traversal of BST:" << endl;
			bstTrial.postorder(root);
			cout << endl;
			break;

		case '6':	//Try to print BST
			cout << "Display BST:" << endl;
			bstTrial.display(root, 1);
			cout << endl;
			break;

		case '7':	//Calculate tree depth
			break;

		case '8':	//Delete the whole tree

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

/*
 * Find Element in the Tree
 */
void BST::find(int item, node** par, node** loc)
{
	node* ptr, * ptrsave;
	if (root == NULL)
	{
		*loc = NULL;
		*par = NULL;
		return;
	}
	if (item == root->key)
	{
		*loc = root;
		*par = NULL;
		return;
	}
	if (item < root->key)
		ptr = root->left;
	else
		ptr = root->right;
	ptrsave = root;
	while (ptr != NULL)
	{
		if (item == ptr->key)
		{
			*loc = ptr;
			*par = ptrsave;
			return;
		}
		ptrsave = ptr;
		if (item < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	*loc = NULL;
	*par = ptrsave;
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(node* tree, node* newnode)
{
	if (root == NULL)
	{
		root = new node;
		root->key = newnode->key;
		root->left = NULL;
		root->right = NULL;
		cout << "Root Node is Added" << endl;
		return;
	}
	if (tree->key > newnode->key)
	{
		if (tree->left != NULL)
		{
			insert(tree->left, newnode);
		}
		else
		{
			tree->left = newnode;
			(tree->left)->left = NULL;
			(tree->left)->right = NULL;
			cout << "Node Added To Left" << endl;
			return;
		}
	}
	else
	{
		if (tree->right != NULL)
		{
			insert(tree->right, newnode);
		}
		else
		{
			tree->right = newnode;
			(tree->right)->left = NULL;
			(tree->right)->right = NULL;
			cout << "Node Added To Right" << endl;
			return;
		}
	}
}

/*
 * Delete Element from the tree
 */
void BST::del(int item)
{
	node* parent, * location;
	if (root == NULL)
	{
		cout << "Tree empty" << endl;
		return;
	}
	find(item, &parent, &location);
	if (location == NULL)
	{
		cout << "Item not present in tree" << endl;
		return;
	}
	if (location->left == NULL && location->right == NULL)
		case_a(parent, location);
	if (location->left != NULL && location->right == NULL)
		case_b(parent, location);
	if (location->left == NULL && location->right != NULL)
		case_b(parent, location);
	if (location->left != NULL && location->right != NULL)
		case_c(parent, location);
	free(location);
	cout << "Element deleted successfully.";
}

/*
 * Case A
 */
void BST::case_a(node* par, node* loc)
{
	if (par == NULL)
	{
		root = NULL;
	}
	else
	{
		if (loc == par->left)
			par->left = NULL;
		else
			par->right = NULL;
	}
}

/*
 * Case B
 */
void BST::case_b(node* par, node* loc)
{
	node* child;
	if (loc->left != NULL)
		child = loc->left;
	else
		child = loc->right;
	if (par == NULL)
	{
		root = child;
	}
	else
	{
		if (loc == par->left)
			par->left = child;
		else
			par->right = child;
	}
}

/*
 * Case C
 */
void BST::case_c(node* par, node* loc)
{
	node* ptr, * ptrsave, * suc, * parsuc;
	ptrsave = loc;
	ptr = loc->right;
	while (ptr->left != NULL)
	{
		ptrsave = ptr;
		ptr = ptr->left;
	}
	suc = ptr;
	parsuc = ptrsave;
	if (suc->left == NULL && suc->right == NULL)
		case_a(parsuc, suc);
	else
		case_b(parsuc, suc);
	if (par == NULL)
	{
		root = suc;
	}
	else
	{
		if (loc == par->left)
			par->left = suc;
		else
			par->right = suc;
	}
	suc->left = loc->left;
	suc->right = loc->right;
}

/*
 * Pre Order Traversal
 */
void BST::preorder(node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		cout << ptr->key << "  ";
		preorder(ptr->left);
		preorder(ptr->right);
	}
}
/*
 * In Order Traversal
 */
void BST::inorder(node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		inorder(ptr->left);
		cout << ptr->key << "  ";
		inorder(ptr->right);
	}
}

/*
 * Postorder Traversal
 */
void BST::postorder(node* ptr)
{
	if (root == NULL)
	{
		cout << "Tree is empty" << endl;
		return;
	}
	if (ptr != NULL)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->key << "  ";
	}
}

/*
 * Display Tree Structure
 */
void BST::display(node* ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root->:  ";
		else
		{
			for (i = 0; i < level; i++)
				cout << "       ";
		}
		cout << ptr->key;
		display(ptr->left, level + 1);
	}
}