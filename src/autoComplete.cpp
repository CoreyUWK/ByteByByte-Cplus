/*
 * autoComplete.cpp
 *
 *  Created on: 2019-09-02
 *      Author: ckirsch
 */
#include "autoComplete.h"
#include <iostream>
#include <cassert>
#include <unordered_set>
using namespace std;

AutoComplete::~AutoComplete()
{
	delete trie;
}

void AutoComplete::insert(string word)
{
	Node *trieNode = trie;
	const int lastCharIdx = word.size() - 1;

	// Handle all character but that last
	for (int i = 0; i < lastCharIdx; ++i)
	{
		char c = word[i];
		if (trieNode->words.find(c) == trieNode->words.end())
		{
			trieNode->words[c] = Element(false, new Node());
		}

		trieNode = trieNode->words[c].nextNode;
	}

	// Handle last
	if (trieNode->words.find(word[lastCharIdx]) == trieNode->words.end())
	{
		trieNode->words[word[lastCharIdx]] = Element(true);
	}
	else
	{
		trieNode->words[word[lastCharIdx]].endOfWord = true;
	}
}


void AutoComplete::GetWords(Node *trieNode, string prefix, vector<string> &words)
{
	if (nullptr == trieNode)
	{
		return;
	}

	// Loop over characters in possible words
	for (auto pair : trieNode->words)
	{
		string newPrefix = prefix + pair.first;
		if (trieNode->words[pair.first].endOfWord)
		{
			words.push_back(newPrefix);
		}
		GetWords(trieNode->words[pair.first].nextNode, newPrefix, words);
	}
}


vector<string> AutoComplete::find(string prefix)
{
	vector<string> words;
	Node *trieNode = trie;

	// Go to last character in prefix in trie O(n)
	for (int i = 0; i < ((int)prefix.size() - 1); ++i)
	{
		if (trieNode == nullptr)
		{
			// Could not find full prefix in trie
			return words;
		}
		else if (trieNode->words.find(prefix[i]) == trieNode->words.end())
		{
			// Could not find full prefix in trie
			return words;
		}

		trieNode = trieNode->words[prefix[i]].nextNode;
	}

	// Check last character of prefix
	if (trieNode->words.find(prefix[prefix.size() - 1]) == trieNode->words.end())
	{
		// Could not find full prefix in trie
		return words;
	}

	// Now should be pointing to end of prefix in trie
	// Get words
	if (trieNode->words[prefix[prefix.size() - 1]].endOfWord)
	{
		words.push_back(prefix);
	}
	trieNode = trieNode->words[prefix[prefix.size() - 1]].nextNode;

	GetWords(trieNode, prefix, words);
	return words;
}


// 2
void AutoComplete2::insertWord(string word)
{
	Node *cur = trie;

	for (uint i = 0; i < word.size(); ++i)
	{
		if (cur->children.find(word[i]) == cur->children.end())
		{
			cur->children[word[i]] = new Node(word.substr(0, i + 1));
		}
		cur = cur->children[word[i]];
	}

	cur->isWord = true;
}

AutoComplete2::AutoComplete2(vector<string> dictionary)
{
	trie = new Node("");
	for (string word : dictionary)
	{
		insertWord(word);
	}
}


void AutoComplete2::findAllChildWords(Node *cur, vector<string> &results)
{
	if (cur->isWord)
	{
		results.push_back(cur->prefix);
	}

	for (auto pair : cur->children)
	{
		findAllChildWords(pair.second, results);
	}
}


vector<string> AutoComplete2::getWordsForPrefix(string prefix)
{
	vector<string> results;

	// Move to prefix node
	Node *cur = trie;
	for (char c : prefix)
	{
		if (cur->children.find(c) != cur->children.end())
		{
			cur = cur->children[c];
		}
		else
		{
			return results;
		}
	}

	// Find all children of prefix
	findAllChildWords(cur, results);

	return results;
}


void autoCompleteMain()
{
	bool pass = true;

	const vector<string> words = {"abc", "acd", "bcd", "def", "a", "aba"};

	AutoComplete trie;
	for (auto word : words)
	{
		trie.insert(word);
	}

	// Set expected results
	unordered_set<string> check;
	check.insert("a");
	check.insert("acd");
	check.insert("aba");
	check.insert("abc");

	uint foundCount = 0;

	// 1
	vector<string> foundWords = trie.find("a");
	for (auto foundWord : foundWords)
	{
		if (check.find(foundWord) == check.end())
		{
			assert(pass &= false);
		}
		++foundCount;
	}
	assert(pass &= (foundCount == check.size()));

	// 2
	AutoComplete2 trie2(words);
	foundWords = trie2.getWordsForPrefix("a");

	foundCount = 0;
	for (auto foundWord : foundWords)
	{
		if (check.find(foundWord) == check.end())
		{
			assert(pass &= false);
		}
		++foundCount;
	}
	assert(pass &= (foundCount == check.size()));

	cout << "Pass: " << pass << endl;
}

//-------------------------------------------------------
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <memory>
#include <stack>
using namespace std;

class AutoComplete_Latest {
    struct Node {
        bool sentenceEnd;
        unordered_map<char, unique_ptr<Node>> children;
        
        Node() : sentenceEnd(false) {}
    };
    
    unordered_map<char, unique_ptr<Node>> trie;
    
    void wordsHelper(string &prefix, vector<string> &list, Node *n) {
        if (n->sentenceEnd) {
            list.push_back(prefix);
        }
        
        for (auto &c : n->children) {
            prefix += c.first;
            wordsHelper(prefix, list, c.second.get());
            prefix.pop_back();
        }
    }
    
    public:
    vector<string> words(string prefix) {
        unordered_map<char, unique_ptr<Node>> *cur = &trie;
        Node *n;
        vector<string> words;

        bool foundPrefix = true;
        for (auto c : prefix) {
            if (cur->find(c) == cur->end()) {
                foundPrefix = false;
                break;
            }
            n = (*cur)[c].get();
            cur = &( (*cur)[c].get()->children);
        }
        if (!foundPrefix) {
            return words;
        }

        wordsHelper(prefix, words, n);
        
        return words;
    }
    
    void insert(string word) {
    	auto *cur = &trie;
    	Node *n;
        for (auto c : word) {
            if ( (*cur).find(c) == (*cur).end() ) {
                cur->emplace ( c, make_unique<Node>() );
            }
            n = (*cur)[c].get();
            cur = &(n->children);
        }
        n->sentenceEnd = true;
    }
};

int main_latest() {
	const vector<string> words = {"abc", "acd", "bcd", "def", "a", "aba"};
	AutoComplete_Latest trie;
	for (auto word : words)
	{
		trie.insert(word);
	}
	
	vector<string> foundWords = trie.words("a");
    for (auto words : foundWords) {
        cout << words << endl;
    }

    return 0;
}