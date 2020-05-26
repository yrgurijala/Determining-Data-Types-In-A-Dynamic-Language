#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
#include "Header1.h"
#include "stdio.h"
using namespace std;

node* head = NULL;

string listManagement(string a)
{
	string check = "";
	int i = 1;

	while (i < a.length())
	{
		if (i != ',')
		{
			check += a[i];
		}
		else
			i = a.length();

		i++;
	}

	if (check[0] == '"')
		return "lists";
	else
		return "listi";
}

string returnDataType(string a)
{
	if (a[0] == '"')
		return "str";
	else if (a[0] == '[')
		return listManagement(a);
	else if (a == "true" || a == "false")
		return "bool";
	else
		return "int";
}

string returnDataType2(string a)
{
	variableList myVariablesList;
	variableList operandList;
	int i = 0;
	string check = "";

	while (i < a.length())
	{
		if (a[i] != '+' && a[i] != '*')
			check += a[i];
		else
		{
			string operand = "";
			operand += a[i];
			operandList.push(operand, "operand");

			if (checkTree(head, check))
				myVariablesList.push(check, getDataTypeFromTree(head,check));
			else
				myVariablesList.push(check, returnDataType(check));

			check = "";
		}

		i++;
	}

	if (check != "")
	{
		if (checkTree(head, check))
			myVariablesList.push(check, getDataTypeFromTree(head, check));
		else
			myVariablesList.push(check, returnDataType(check));
	}

	return myVariablesList.determineDataType(operandList);
}

string returnDataType3(string a)
{
	variableList myVariablesList;
	int i = 0;
	string check = "";
	a = a.substr(a.find('(')+1, a.length());

	while (i < a.length())
	{
		if (a[i] != ',' && a[i] != ')')
			check += a[i];
		else
		{
			if (checkTree(head, check))
				myVariablesList.push(check, getDataTypeFromTree(head, check));
			else
				myVariablesList.push(check, returnDataType(check));

			check = "";
		}

		i++;
	}

	if (check != "")
	{
		if (checkTree(head, check))
			myVariablesList.push(check, getDataTypeFromTree(head, check));
		else
			myVariablesList.push(check, returnDataType(check));
	}

	return myVariablesList.determineDataType(myVariablesList);
}

void checkLine(string a)
{
	string identifier = "";
	string value = "";
	int i = 0;

	while (i < a.length())
	{
		if (a[i] != '=')
		{
			if(a[i] != ' ')
				identifier += a[i];
			i++;
		}
		else
		{
			i++;

			while (i < a.length())
			{
				if (a[i] == '#')
					i = a.length();
				else if (a[i] != '=' && a[i] != ' ')
				{
					value = value+a[i];
				}

				i++;
			}
		}
	}

	if (!checkTree(head, identifier))
	{
		if (value.find('+') < value.length() || value.find('*') < value.length())
			head = insert(identifier, returnDataType2(value), head);
		else if (value.find('(') < value.length())
			head = insert(identifier, returnDataType3(value), head);
		else if (value.find('<') < value.length() || value.find('>') < value.length())
			head = insert(identifier, "bool", head);
		else if (checkTree(head, value))
			head = insert(identifier, getDataTypeFromTree(head, value), head);
		else
			head = insert(identifier, returnDataType(value), head);
	}
	else
	{
		if (value.find('+') < value.length() || value.find('*') < value.length())
			setDataTypeInTree(head, identifier, returnDataType2(value));
		else if (value.find('(') < value.length())
			setDataTypeInTree(head, identifier, returnDataType3(value));
		else if (value.find('<') < value.length() || value.find('>') < value.length())
			setDataTypeInTree(head, identifier, "bool");
		else
			setDataTypeInTree(head, identifier, returnDataType(value));
	}
}

int main(int argc, char** argv)
{
	string filename = "";
	filename += argv[1];
	filename = filename.substr(5, filename.length());

	std::ifstream inputFile(filename.c_str());
	string line;

	while (!inputFile.eof())
	{
		getline(inputFile, line);

		if (line.substr(0,3) == "def")
		{
			while (line.find("return") > line.length())
				getline(inputFile, line);
		}
		else if(line[0] != '#' && line.find("if") > line.length() && line.find("else") > line.length() && line.length() != 0)
			checkLine(line);
	}

	inorder(head);
}