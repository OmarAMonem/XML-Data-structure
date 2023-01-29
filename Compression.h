#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

struct MinHeapNode {
	char data;
	unsigned freq;
	MinHeapNode* left, * right;

	MinHeapNode(char data, unsigned freq)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

MinHeapNode* main_root;

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
void compress(string& str);
