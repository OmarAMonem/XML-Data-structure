#include "./inc/xml.h"

using namespace std;

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
}