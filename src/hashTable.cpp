/*
 * hashTable.cpp
 *
 *  Created on: 2019-08-05
 *      Author: ckirsch
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

namespace hashTable1
{
	#define SIZE 20

	struct DataItem
	{
		int key;
		int data;
	};


	enum cbool
	{
		cfalse = 0,
		ctrue = 1
	};


	struct DataItem* hashArray[SIZE];


	int hashCode(int key)
	{
		return key % SIZE;
	}


	cbool search(int key, int *value)
	{
		int hashIndex = hashCode(key); // Get hash

		// Move in array until empty
		while (hashArray[hashIndex] != NULL)
		{
			// Check if match
			if (hashArray[hashIndex]->key == key)
			{
				*value = hashArray[hashIndex]->data;
				return ctrue;
			}

			// go to next cell
			++hashIndex;
			// Handle wrap around table
			hashIndex %= SIZE;
		}

		return cfalse;
	}


	void insert(int key, int data)
	{
		struct DataItem *item = (struct DataItem *) malloc(sizeof(struct DataItem));
		item->key = key;
		item->data = data;

		// get the hash
		int hashIndex = hashCode(key);

		// Move in array until an empty or deleted cell
		while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
		{
			// go to next cell
			++hashIndex;
			// Handle wrap around table
			hashIndex %= SIZE;
		}

		hashArray[hashIndex] = item;
	}


	void deleteItem(int key)
	{
		int hashIndex = hashCode(key);

		// Move in array until empty
		while (hashArray[hashIndex] != NULL)
		{
			// Check if found key position
			if (hashArray[hashIndex]->key == key)
			{
				free(hashArray[hashIndex]);
				hashArray[hashIndex] = NULL;
				break;
			}

			// go to next cell
			++hashIndex;
			// handle wrap around table
			hashIndex %= SIZE;
		}

		return;
	}


	void display()
	{
		int i = 0;

		for (i = 0; i < SIZE; ++i)
		{
			if (hashArray[i] != NULL)
			{
				printf("(%d,%d) ", hashArray[i]->key, hashArray[i]->data);
			}
			else
			{
				printf("~~ ");
			}
		}
		printf("\n");
	}


	int hashTableMain()
	{
		cbool result = ctrue;
		int data;

		insert(1, 20);
		insert(2, 70);
		insert(42, 80);
		insert(4, 25);
		insert(12, 44);
		insert(14, 32);
		insert(17, 11);
		insert(13, 78);
		insert(37, 97);

		display();
		//result &= search(37, &data);

		if(result)
		{
			printf("Element found: %d\n", data);
		}
		else
		{
		  printf("Element not found\n");
		}

		deleteItem(37);
		//result &= search(37, &data);

		if(result)
		{
			printf("Element found: %d\n", data);
		}
		else
		{
			printf("Element not found\n");
		}

		return 0;
	}
}

