#include "Compression.h"

using namespace std;

// utility function to store characters along with there huffman value in a hash table
void storeCodes(struct MinHeapNode* root, string str, map<char, string>& codes)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0", codes);
	storeCodes(root->right, str + "1", codes);
}

// function iterates through the encoded string code
// if code[i]=='1' then move to node->right
// if code[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
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

// The main function that builds a Huffman Tree
void buildHuffmanCodes(string text)
{
	map<char, int> frequency;
	// store map each character with its frequency in input string
	for (char ch : text)
		frequency[ch]++;
	int size = frequency.size();
	struct MinHeapNode* left, * right, * top;

	// Create a min heap
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (auto freq : frequency)
		minHeap.push(new MinHeapNode(freq.first, freq.second));
	// Iterate while size of heap doesn't become 1
	while (minHeap.size() != 1) {
		// Extract the two minimum freq items from min heap
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();
		// Create a new internal node with frequency equal to the sum of the two nodes frequencies.
		top = new MinHeapNode('$', left->freq + right->freq);
		// Make the two extracted node as left and right children of this new node.
		top->left = left;
		top->right = right;
		// Add this node to the min heap '$' is a special value for internal nodes, not used
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

// Convert a string containing a sequence of 0s and 1s to an actual binary representation.
vector<uint8_t> toBinary(string const& binStr)
{
	vector<uint8_t> result;
	result.reserve(binStr.size() / 24);
	size_t pos = 0;
	size_t len = binStr.length();
	while (pos < len)
	{
		size_t curLen = min(static_cast<size_t>(24), len - pos);
		auto curStr = binStr.substr(pos, curLen) + string(24 - curLen, '0');
		result.push_back(stoi(curStr, 0, 2));
		pos += 24;
	}
	return result;
}