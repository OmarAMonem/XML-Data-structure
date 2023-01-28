#include "xml.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

string Tree::prettify(int level, Node* parent)
{
    string temp = "";
    string output = "";
    if (parent == nullptr)
    {
        parent = root; // start at the begining of the tree
        level = 0;
    }

    for (int i = 0; i < parent->children.size(); i++)
    {
        Node* node = parent->children[i]; // creating pointers to children of the parent node
        string Spacing = "";
        for (int i = 0; i < level; ++i) // spacing with levels, each leavel has an extra 4 spaces more than the above level
        {
            if(i == level -1)
            {
                temp = Spacing;
            }
            Spacing += "\t";
        }
        output += Spacing + "<" + node->key + ">";

        if (node->children.size() > 0)
        {
            output = output + "\n" + prettify(level + 1, node);

            if (i == parent->children.size() - 1)
            {
                output += "\t";
            }
            else
            {
                output += "\n";
            }
        }
        else
        { // if it is leaf node
            if (i == parent->children.size() - 1)
            { // if last node in its level
                output = output + "\n" + Spacing + "\t" + node->value + "\n" + Spacing + "</" + node->key + ">";
            }
            else
            {
                output = output + "\n" + Spacing + "\t" + node->value + "\n" + Spacing  + "</" + node->key + ">\n";
            }
        }

    }
    if(parent->key == "")
    {
        return  output + "\n";
    }

    return output + "\n" + temp + "</" + parent->key + ">"  ;
}

int main()
{
    freopen("prettify.xml", "w", stdout);
    ifstream file;
    file.open("minify.txt");
    if (!file.is_open())
    {
        cout << "Unable to open the file." << endl;
        return 0;
    }
    string line, x;
    while (getline(file, line))
    {
        x = x + line;
    }

    file.close();
    Tree t = parse(x);
    string Result = t.prettify();
    cout << Result;
}
