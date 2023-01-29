#include "./inc/xml.h"

using namespace std;


string Tree::XMLToJson(int level, Node *parent)
{
    string temp;
    string output = "";
    if (parent == nullptr)
    {
        parent = root; // start at the begining of the tree
        level = 0;
    }

    for (int i = 0; i < parent->children.size(); i++)
    {
        Node *node = parent->children[i]; // creating pointers to children of the parent node
        string Spacing = "\t";
        for (int i = 0; i < level; ++i) // spacing with levels, each leavel has an extra 4 spaces more than the above level
        {
            Spacing += "\t";
        }
        output += Spacing + "\"" + node->key + "\": ";

        if (node->children.size() > 0)
        {
            output += XMLToJson(level + 1, node);

            if (i == parent->children.size() - 1)
            {
                output += "\t";
            }
            else
            {
                output += ",\n";
            }
        }
        else
        { // if it is leaf node
            if (i == parent->children.size() - 1)
            { // if last node in its level
                output += "\"" + node->value + "\"";
            }
            else
            {
                output += "\"" + node->value + "\"" + ",\n";
            }
        }
        temp = Spacing;
    }
    return "{\n" + output + "\n" + temp + "}";
}

/*
int main()
{
    freopen("./output/XML_JSON.json", "w", stdout);
    ifstream file;
    file.open("./samples/sample.xml");
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
    string Result = t.XMLToJson();
    cout << Result;
    freopen("./output/minify.txt", "w", stdout);
    cout << minify(x);
}
*/