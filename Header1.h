#include <iostream>
#include <stdlib.h>
using namespace std;

class variable
{
public:
    string identifier;
    string dataType;
    variable* nextVariable;
};

class variableList
{
public:
    variable* head, * tail;

    //This constructor sets the list to null
    variableList()
    {
        head = NULL;
        tail = NULL;
    }

    //This method inserts the command to the bottom of the list
    void push(string a, string b)
    {
        variable* temp = new variable;

        temp->identifier = a;
        temp->dataType = b;
        temp->nextVariable = NULL;

        if (head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->nextVariable = temp;
            tail = temp;
        }
    }

    void print()
    {
        variable* temp = new variable;
        temp = head;

        cout << "List:- \n";
        while (temp != NULL)
        {
            cout << temp->identifier << ":" << temp->dataType << "\n";
            temp = temp->nextVariable;
        }
    }

    string determineDataType(variableList a)
    {
        variable* temp = new variable;
        temp = head;
        string checkDataType = temp->dataType;
        string checkOperator;

        while (temp != NULL)
        {
            if (checkDataType == "bool")
                return "undefined";
            else if (temp->dataType.find("list") < temp->dataType.length() && checkOperator == "+")
                return checkDataType;
            else if (checkDataType != temp->dataType && temp->identifier != " ")
                return "undefined"; 

            if (checkDataType == "str" && checkOperator == "*")
                return "undefined";

            temp = temp->nextVariable;
            checkOperator = a.returnHead();
        }

        return checkDataType;
    }

    string returnHead()
    {
        if (head != NULL)
            return head->identifier;
        else
            return "";
    }

    void deleteHead()
    {
        if (head != NULL)
            head = head->nextVariable;
    }

};
