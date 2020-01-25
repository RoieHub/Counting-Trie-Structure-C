
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define NUM_LETTERS (26) 
#define MAX_WORD (30)
#define MAX_LINE (256)
// typedef enum {FALSE = 0, TRUE = 1} boolean; 
typedef struct node
{
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    char* word;
} node;

// Headers////
node* getNewChildNode(node* father ,char currentLetter);
bool isCapital(char a);
bool IsCharacter(char a);
void Decapitalize(char* input ,int sizeOfInput);
int nextWordLength(char* wordStart, int* offset);
//void InitTreeByText(node* root, char* text);
void PreparingTheText(char* word,node* root);
void updateWordInTrie(node* root , char* word, int length);
void printLexi(node* root);
void printRevLexi(node* root);

int main(int argc, char *argv[])
{
    node root;
    int i;
    root.count = 0;
    root.word = malloc(1);
    *root.word = '\0';
    for (i = 0; i < NUM_LETTERS; i++){
        root.children[i] = NULL;
    }

	char string[100];
    while(fgets(string, 100, stdin))
    {
	    PreparingTheText(string, &root);
    }

    if(argc == 1)
    {
        printLexi(&root); 
    }
    else
    {
        printRevLexi(&root);
    }
	return 0 ;
}

void printLexi(node* root)
{
	int i;	
    if(root->count)
	{
		printf("%s\t%ld\n", root->word, root->count);
	}
    free(root->word);
	for(i = 0 ; i < NUM_LETTERS ; i++)
	{
		if(root->children[i] != NULL)
		{
			printLexi(root->children[i]);
            free (root->children[i]);
		}
	}
}
void printRevLexi(node* root)
{
    int i;
    for(i = NUM_LETTERS - 1 ; i >= 0; i--)
    {
        if(root->children[i] != NULL)
        {
            printRevLexi(root->children[i]);
            free(root->children[i]);
        }
    }
    if(root->count)
	{
		printf("%s\t%ld\n", root->word, root->count);
	}
    free (root->word);
}

// This methods work on a Valid word ONLY!
void updateWordInTrie(node* root , char* word, int length)
{
	int i = 0;
	char currentLetter  = word[0];
	node* currentNode = root;
	// Init children index
	int letterIndex = currentLetter - 'a';
	// At this point there is a Child to our Root.
	while(true)
	{
		if (currentNode->children[letterIndex] == NULL)
		{
			// Create if not exist.
			currentNode->children[letterIndex] = getNewChildNode(currentNode ,currentLetter);
		}

        // Last letter of the word
		if (i == (length - 1))
		{
			currentNode = currentNode->children[letterIndex]; // Set current Node to be his proper child
			currentNode->count++;
            return;
		}
		else
        {
			currentNode = currentNode->children[letterIndex]; // Set current Node to be his proper child
			currentLetter = word[++i];
			letterIndex = currentLetter - 'a';
		}
	}
}

node* getNewChildNode(node* father ,char currentLetter)
{
    int i = 0;
    // Create the node
	node* Node = malloc(sizeof(node));
    char* fathersWord = father->word;
    // Set count to 0
    Node->count = 0;
    size_t fWordLen = strlen(father->word);
    // Set all children to NULL
	for ( i = 0; i < NUM_LETTERS; i++)
		Node->children[i] = NULL;
    // Set Word
    char *newWord = malloc(fWordLen + 2); //+1  +1 for the null-terminator
    strcpy(newWord,fathersWord);
    newWord[fWordLen] = currentLetter;
    newWord[fWordLen + 1] = '\0';
    Node->word = newWord;
    // Set Letter;
    return Node;
}

void PreparingTheText(char* line ,node* root)
{
	int next_Word_Length = 0;
    int i = 0;
    int size = strlen(line);
    Decapitalize(line,size);
    int offset = 0;
    next_Word_Length = nextWordLength(line, &i);
    while(next_Word_Length != 0)
    {
        char* currentWord = malloc(next_Word_Length + 1); //chacnge word to lower
        memcpy(currentWord, &line[i + offset], next_Word_Length);
        currentWord[next_Word_Length] = '\0';
        updateWordInTrie(root , currentWord, next_Word_Length);
        free(currentWord);

        i = i + next_Word_Length + offset;
        next_Word_Length = nextWordLength(&line[i], &offset);
        
    }
}

bool IsCharacter(char a)
{
    return ((a >= 'a') && (a <= 'z'));
}
bool isCapital(char a)
{
    return((a >= 'A') && (a <= 'Z'));
}

void Decapitalize(char* input,int sizeOfInput)
{
    int i ;
    int DIST = 'a' - 'A';
    for(i = 0; i < sizeOfInput; i++)
    {
        if(isCapital(input[i]))
        {
            input[i] += DIST;
        }
    }
}

int nextWordLength(char* wordStart, int* offset)
{
    int offsetCounter = 0;
    while(!IsCharacter(wordStart[offsetCounter]))
    {
        if (wordStart[offsetCounter] == '\0')
        {
            return 0;
        }

        offsetCounter++;
    }

    int wordLength = 0;

    // Finding the length of the Word
    while(IsCharacter(wordStart[offsetCounter + wordLength]))
    {
        wordLength++;
    }

    *offset = offsetCounter;
    return wordLength;     
}



