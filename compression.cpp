#include "Compression.h"

using namespace std;

void storeCodes(struct MinHeapNode* root, string str, map<char, string>& codes)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0", codes);
	storeCodes(root->right, str + "1", codes);
}

string decoding(struct MinHeapNode* root, string code)
{
	string res = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < code.size(); i++)
	{
		if (code[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;
		if (curr->left == nullptr && curr->right == nullptr)
		{
			res += curr->data;
			curr = root;
		}
	}

	return res + '\n';
}

void buildHuffmanCodes(string text)
{
	map<char, int> frequency;
	for (char ch : text)
		frequency[ch]++;
	int size = frequency.size();
	struct MinHeapNode* left, * right, * top;

	// Create a min heap
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (auto freq : frequency)
		minHeap.push(new MinHeapNode(freq.first, freq.second));

	while (minHeap.size() != 1) {

		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();
		top = new MinHeapNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}
	main_root = minHeap.top();
}

string Huffman_encoding(string text)
{
	buildHuffmanCodes(text);

	string encoded = "";
	map<char, string> StringEncoded;
	storeCodes(main_root, "", StringEncoded);

	for (char ch : text) {
		encoded += StringEncoded[ch];
	}
	return encoded;
}

vector<uint8_t> toBinary(std::string const& binStr)
{
	std::vector<uint8_t> result;
	result.reserve(binStr.size() / 8);
	size_t pos = 0;
	size_t len = binStr.length();
	while (pos < len)
	{
		size_t curLen = std::min(static_cast<size_t>(8), len - pos);
		auto curStr = binStr.substr(pos, curLen) + std::string(8 - curLen, '0');
		std::cout << "curLen: " << curLen << ", curStr: " << curStr << "\n";
		result.push_back(std::stoi(curStr, 0, 2));
		pos += 8;
	}
	return result;
}

void compress(string& str)
{
	ofstream fout("my_output.txt");
	if (fout.fail())
	{
		cout << "Can't open the file.\n";
		return;
	}
	string coded = Huffman_encoding(str);
	auto bin = toBinary(coded);
	for (auto i : bin)
	{
		fout << static_cast<uint8_t>(i) << " ";
	}
}

int main()
{
	string str;
	string path = "notes.txt";
	fstream file_handler(path.c_str());
	if (file_handler.fail())
	{
		cout << "Can't open the file.\n";
		return 0;
	}
	string line;
	while (getline(file_handler, line))
		str = line;
	file_handler.close();
	compress(str);

	uint8_t ch = 'ø';
	return 0;
}
