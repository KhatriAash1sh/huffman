#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

// A Tree node
struct Node {
	char ch;
	int freq;
	Node* left, * right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}
void buildHuffmanTree(string text)
{
	cout << "char." << "\tFreq.no" << endl;

	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
		char targetChar = ch;
	}
	for (const auto& pair : freq) {
		cout << pair.first << "\t " << pair.second << endl;
	}


	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "\nHuffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}
int main()
{
	//read file
	//string filePath = "your_file.txt";
	string filePath;
	cout<<"Enter the filepath: ";
	cin>>filePath;
	ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		cerr << "Error opening the file: " << filePath << endl;
		return 1;
	}

	string data;
	while (getline(inputFile, data)) {
		cout << data << endl;
	}
	inputFile.close();
	//string data;
	//cout << "enter the text:";
	//getline(cin, data);
	string text = (data);

	buildHuffmanTree(text);

	return 0;
}
