#include <iostream>
using namespace std;

struct node
{
	string identifier;
	string dataType;
	node* left;
	node* right;
};

node * newNode(string a, string b)
{
	node* newNode = new node;
	
	newNode->identifier = a;
	newNode->dataType = b;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

node* insert(string a, string b, node* ref)
{
	if (ref == NULL)
		return newNode(a, b);

	if (a < ref->identifier)
		ref->left = insert(a, b, ref->left);
	else
		ref->right = insert(a, b, ref->right);

	return ref;
}

void inorder(node* ref)
{
	if (ref == NULL)
		return;

	inorder(ref->left);

	if(ref->dataType.find("list") < ref->dataType.length())
		cout << ref->identifier << ": " << "list" << '\n';
	else
		cout << ref->identifier << ": " << ref->dataType << '\n';

	inorder(ref->right);
}

bool checkTree(node* ref, string a)
{
	node* temp = ref;

	while (temp != NULL)
	{
		if (temp->identifier == a)
			return true;
		else if (temp->identifier > a)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return false;
}

string getDataTypeFromTree(node* ref, string a)
{
	node* temp = ref;

	while (temp != NULL)
	{
		if (temp->identifier == a)
			return temp->dataType;
		else if (temp->identifier > a)
			temp = temp->left;
		else
			temp = temp->right;
	}
}

void setDataTypeInTree(node* ref, string a, string b)
{
	node* temp = ref;

	while (temp != NULL)
	{
		if (temp->identifier == a)
		{
			temp->dataType = b;
			return;
		}
		else if (temp->identifier > a)
			temp = temp->left;
		else
			temp = temp->right;
	}
}

