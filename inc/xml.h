#ifndef XML_TO_JSON_H
#define XML_TO_JSON_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>

using namespace std;

class Node
{
public:
    string key;
    string value;
    vector<Node *> children;

    void setvalue(string value)
    {
        this->value = value;
    }

    friend class Tree;
};

class Tree
{
public:
    Node *root;

    void setroot(Node *root)
    {
        this->root = root;
    }
    void addNode(Node *node, Node *parent)
    {
        if (parent == nullptr)
        {
            parent = root;
        }
        parent->children.push_back(node);
    }

    string XMLToJson(int level = 0, Node *parent = nullptr);    
};

/*****************************************************************
*                       Minify Functions                         *
* Trim and minify Functions to minify spaces from the XML string *
*****************************************************************/
std::string trim(const std::string &str, const std::string &whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}
std::string minify(const std::string &str, const std::string &fill = " ", const std::string &whitespace = " \t")
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}
/*****************************************************************
*                                                                *
*****************************************************************/

/*****************************************************************
*                       XML to Json Functions                    *
*               Function to convert XML string to a tree         *
*****************************************************************/
Tree parse(string input_string)
{
    stack<Node *> parse_stack;
    string first_tag;
    string start_of_tag = "<";
    string end_of_tag = ">";
    unsigned int i = input_string.find(start_of_tag, 0), start_tag_index = 0, end_tag_index, j;

    // remove <?xml ?> tag from the string
    if (input_string.substr(i + 1, 1) == "?")
    {
        j = input_string.find(end_of_tag, i);
        input_string.erase(i, j - i + 1);
    }

    start_tag_index = input_string.find(start_of_tag, start_tag_index); // find the index of the < in the first tag
    end_tag_index = input_string.find(end_of_tag, start_tag_index);     // find the index of the > in the first tag
    first_tag = input_string.substr(start_tag_index + 1, end_tag_index - start_tag_index - 1);

    Node *root = new Node;
    Node *node = new Node;
    node->key = first_tag;
    Tree xml_tree;

    xml_tree.setroot(root);
    xml_tree.addNode(node, root);
    start_tag_index = input_string.find(start_of_tag, end_tag_index); // find the index of the < after the end of the first tag
    end_tag_index = input_string.find(end_of_tag, start_tag_index);   // find the index of the > after the end of the first tag

    Node *parent = node; // setting parent node to the first node in the tree with the first tag name

    while (input_string.find(start_of_tag, end_tag_index) != string::npos) // loop all over the xml string till the end
    {
        if (input_string.substr(start_tag_index + 1, 1) != "/") // if starting tage found. ex. <tagname>
        {
            Node *newnode = new Node;
            newnode->key = input_string.substr(start_tag_index + 1, end_tag_index - start_tag_index - 1); // extract the key from the xml
            xml_tree.addNode(newnode, parent);
            start_tag_index = input_string.find(start_of_tag, end_tag_index); // get index of "<" of the next tag
            if (start_tag_index != string::npos)
            { // extract the value / data from the xml. The sub-string between the start and end tags
                newnode->value = minify(input_string.substr(end_tag_index + 1, start_tag_index - end_tag_index - 1));
                if (input_string.substr(start_tag_index + 1, 1) != "/") // if the next tag is a start tag
                {
                    parse_stack.push(parent);
                    parent = newnode;
                }
            }
            end_tag_index = input_string.find(end_of_tag, start_tag_index); // get index of ">" of the next tag
        }
        if (input_string.substr(start_tag_index + 1, 1) == "/") // if ending tag found. ex. </tagname>
        {
            start_tag_index = input_string.find(start_of_tag, end_tag_index);
            end_tag_index = input_string.find(end_of_tag, start_tag_index);
            if (start_tag_index != string::npos)
            {
                if (input_string.substr(start_tag_index + 1, 1) == "/")
                {
                    if (!parse_stack.empty())
                    {
                        parent = parse_stack.top();
                        parse_stack.pop();
                    }
                }
            }
        }
    }
    return xml_tree; // return pointer to the tree
}

#endif