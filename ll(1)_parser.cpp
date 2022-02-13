/*
 our grammar
	 S→(Χ)

	 Χ→ΥΖ

	 Υ→α | β | S

	 Ζ→*Χ | -Χ |+Χ| ε
 */

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
//check if given string is terminal
bool isTerminal(string compChar)
{
	const string terminalChar[9] = { "(", ")", "a", "b", "*", "-", "+", " ", "$" };
	for (int k = 0; k < 9; k++)
	{
		if (compChar == terminalChar[k])
		{
			return true;
		}
	}
	return false;
}
//implementation of syntax analysis table -- returns string "N/A" if is not found, if found returns reversed rule
string syntaxTable(string compChar, string stackTop)
{
	//the syntax table
	string grammarSyntaxTable[5][9] = { {"N/A", "(", ")", "a", "b", "*", "-", "+", "$"},
										{"S", "(X)", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A"},
										{"X", "YZ", "N/A", "YZ", "YZ", "N/A", "N/A", "N/A", "N/A"},
										{"Y", "S", "N/A", "a", "b", "N/A", "N/A", "N/A", "N/A",},
										{"Z", "N/A", " ", "N/A", "N/A", "*X", "-X", "+X", "N/A"} };
	//find positions in array
	int posX = 0;
	int posY = 0;
	for (int x = 0; x < 5; x++)
	{
		if (stackTop == grammarSyntaxTable[x][0])
		{

			posX = x;
		}
	}
	for (int y = 0; y < 9; y++)
	{
		if (compChar == grammarSyntaxTable[0][y])
		{
			posY = y;
		}
	}
	string returnString = grammarSyntaxTable[posX][posY];
	if (returnString != "N/A")
	{
		reverse(returnString.begin(), returnString.end());
	}
	return returnString;

}
int main()
{
	//string to be checked if is valid for grammar
	string toCheck = "((b-a)*(a+b))";
	cout << toCheck << endl;
	string padding = "$";
	toCheck += padding;
	//creating our stack
	stack<string> stringStack;
	stringStack.push("$");
	stringStack.push("S");

	//if finished = 0 still running, = 1 accepted string, = -1 denied string
	int finished = 0;
	int currentPos = 0;
	while (finished == 0 && currentPos < toCheck.length())
	{
		string compChar(1, toCheck[currentPos]);
		//cases for syntax analysis
		if (isTerminal(stringStack.top()))
		{	//character has been accepted and removed from stack
			if (compChar == stringStack.top() && compChar != "$")
			{
				stringStack.pop();
				currentPos++;
			}
			//syntax check completed and string accepted
			else if (compChar == stringStack.top() && stringStack.top() == "$")
			{
				finished = 1;


			}
			else if (compChar != stringStack.top())
			{
				finished = -1;
			}
		}
		else {
			string syntaxTableString = syntaxTable(compChar, stringStack.top());
			if (syntaxTableString == "N/A")
			{
				finished = -1;



			}
			else
			{
				stringStack.pop();
				if (syntaxTableString != " ")
				{
					for (int k = 0; k < syntaxTableString.length(); k++)
					{
						string toPush(1, syntaxTableString[k]);
						stringStack.push(toPush);
					}
				}
			}
		}
	}
	if (finished == -1)
	{
		cout << "The input string is not accepted." << endl;
	}
	else if (finished == 1)
	{
		cout << "The input string is accepted." << endl;
	}


}

