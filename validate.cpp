

#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "xml.h"
using namespace std;

bool validate(string uncorrected_file){
    stack<string> Stack;
    int j ,k ;
    string y ;
    bool flag=false ;
    ifstream file;
    file.open(uncorrected_file);
    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
        return 0;
    }
    string line, x ="";
    while (getline(file, line))
    {
        line += "\n" ;
        x+=line ;                                    //convert the file into a string
    }
    file.close();
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
                flag=true ;
            }
            else if (y == Stack.top())            //check if the closing tag name is the same as that of the opening in the stack
            {
                Stack.pop();
            }else{
                x.replace(i+2,k-(i+2), Stack.top()); // if not replace the closing tag by an opening one
                Stack.pop();
                flag=true ;
            }

        }
    }
    freopen("corrected_file.xml", "w", stdout);
    cout<<x ;
    freopen("CON","w",stdout);
    return flag;

}



int main()
{
    bool x =validate("sample.xml") ;
    cout<<x ;

}

