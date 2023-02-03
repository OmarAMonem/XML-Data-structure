#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
#include <bitset>

using namespace std;

// A Huffman tree node
struct MinHeapNode {
	// One of the input characters
	char data;
	// Frequency of the character
	unsigned freq;
	// Left and right child of this node
	MinHeapNode* left, * right;

	MinHeapNode(char data, unsigned freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

MinHeapNode* main_root;

// For comparison of two heap nodes (needed in min heap)
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r)

	{
		return (l->freq > r->freq);
	}
};

void storeCodes(struct MinHeapNode* root, string str, map<char, string>& codes);
string decoding(struct MinHeapNode* root, string code);
void buildHuffmanCodes(string text);
string Huffman_encoding(string text);
vector<uint8_t> toBinary(string const& binStr);