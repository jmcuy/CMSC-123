#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct LinkedList {
	char* listFile;
	struct LinkedList* rest;
} LinkedList;

LinkedList createList() {
	LinkedList root = {NULL, NULL};
	return root;
}

void addList(char* listFile, LinkedList* root) {
	if(root->listFile == NULL && root->rest == NULL) {
		root->listFile = listFile;
	} else if(root->listFile != NULL && root->rest == NULL){
		LinkedList* next = (LinkedList*) malloc(sizeof(LinkedList));
		next->listFile = (char*) malloc(sizeof(listFile));
		next->listFile = listFile;
		next->rest = NULL;
		root->rest = next;
	} else {
		addList(listFile, root->rest);
	}
}

bool isInsideList(char* listFile, LinkedList* root) {
	if(root->listFile != NULL) {
		printf("%s == %s\n", listFile, root->listFile);
		if(strcmp(root->listFile, listFile) == 0) {
			return true;
		} else {
			if(root->rest == NULL) {
				return false;
			} else {
				isInsideList(listFile, root->rest);
			}
		}
	}
}

void displayList(LinkedList* root) {
	if(root->listFile != NULL && root->rest != NULL) {
		printf("%s\n", root->listFile);
		displayList(root->rest);
	} else if(root->listFile != NULL && root->rest == NULL) {
		printf("%s\n", root->listFile);
	} else {
		return;
	}
}

