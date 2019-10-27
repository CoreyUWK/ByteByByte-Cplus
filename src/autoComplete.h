/*
 * autoComplete.h
 *
 *  Created on: 2019-09-02
 *      Author: ckirsch
 */

#ifndef AUTOCOMPLETE_H_
#define AUTOCOMPLETE_H_
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;


class AutoComplete
{
	struct Node;
	struct Element;

	struct Element
	{
		bool endOfWord;
		Node *nextNode;
		Element(bool endOfWord = false, Node *nextNode = nullptr) :
			endOfWord(endOfWord), nextNode(nextNode) {}
	};

	struct Node
	{
		unordered_map<char, Element> words;
	};

	Node *trie;

	void GetWords(Node *trieNode, string prefix, vector<string> &words);
public:
	AutoComplete() : trie(new Node()) {}
	~AutoComplete();

	void insert(string word);

	/* If wanted brute force than for every dictionary word O(n) check starts with prefix O(m)
	 * => O(n*m) */
	vector<string> find(string prefix);
};


// Sam's Class design
class AutoComplete2
{
	struct Node
	{
		string prefix;
		bool isWord;
		unordered_map<char, Node*> children;

		Node (string prefix) : prefix(prefix), isWord(false) {}
	};

	Node *trie;

	void insertWord(string s);
	void findAllChildWords(Node *cur, vector<string> &results);
	void GetWords(Node *trieNode, string prefix, vector<string> &words);
public:
	AutoComplete2(vector<string> dictionary);
	vector<string> getWordsForPrefix(string prefix);
};



void autoCompleteMain();


#endif /* AUTOCOMPLETE_H_ */
