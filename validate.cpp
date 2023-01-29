#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "xml.h"
using namespace std;

string validate(string x){
    stack<string> Stack;
    int j ,k ;
    string y ;
    for(int i = 0; x[i] != '\0'; i++)
    {
        if (x[i] == '<' && x[i + 1] != '/')         // finding opening tag
        {
            for (j = i + 1; x[j] != '>'; j++);      // loop to get the index of the end of the opening tag

            Stack.push(x.substr(i+1, j-(i+1)));     //put the opening tag name in the stack
        }else if(x[i] == '<' && x[i + 1] == '/'){   //finding closing tag

            for (k = i + 2; x[k] != '>'; k++);     // loop to get the index of the end of the closing tag
            y = x.substr(i+2, k-(i+2));

            if(Stack.empty()){                    // in case there is a closing tag without an opening tag
                x.erase(i,k-i+1);
            }
            else if (y == Stack.top())            //check if the closing tag name is the same as that of the opening in the stack
            {
                Stack.pop();
            }else{
                x.replace(i+2,k-(i+2), Stack.top()); // if not replace the closing tag by an opening one
                Stack.pop();
            }

        }
    }
    while(!Stack.empty())
    {
        x += "</" + Stack.top() + ">";
        Stack.pop();
        x += "\n";
    }
    return x;
}