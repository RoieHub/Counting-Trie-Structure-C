
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
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    char* word;

} node;


// Headers////
node* getNewChildNode(node* father ,char currentLetter);
bool isCapital(char a);
bool IsCharacter(char a);
node* initTrieRoot();
char* Decapitalize(char* input ,int sizeOfInput);
int nextWordLength(char* wordStart);
char* wordString(char* startOfWord);
//void InitTreeByText(node* root, char* text);
int textSize(char*text);
node* PreParringTheText(char* word,node* root);
int updateWordInTrie(node* root , char* word);
void printLexi(node* root);
void printRevLexi(node* root);
bool noChildren(node* root);

int main(int argc, char *argv[])
{
     node* root = initTrieRoot();
	char string[100];
    while(fgets(string, 100,stdin))
    {
	    PreParringTheText(string,root);
    }

  if(argc == 1)
            printLexi(root); 
        else
        {
        
            printRevLexi(root);
        }

    free(root);
  //  free(string); what to do?
	return 0 ;
}

bool noChildren(node* root)
{
	bool noChildFound = true;
	int i;
	for(i = 0 ; (i < NUM_LETTERS) && (noChildFound) ; i++ )
		noChildFound = ((root->children[i]) == NULL);
	return noChildFound;
}

void printLexi(node* root)
{

	int i;

	// Stop condition
	if(noChildren(root) || root->count)
	{
		printf("%s%c\t%d\n",root->word,root->letter,root->count);
	}

	for(i = 0 ; i < NUM_LETTERS ; i++)
	{
		if(root->children[i] != NULL)
		{
			printLexi(root->children[i]);
		}


	}


}
void printRevLexi(node* root)
{
	int i;
	if(noChildren(root) && root->count)
	{
		printf("%s%c\t%d\n",root->word,root->letter,root->count);
		free(root);
	}
	else{
		for(i = NUM_LETTERS-1 ; i > -1 ; i--)
		{
			if(root->children[i] != NULL)
			{
				printRevLexi(root->children[i]);
				root->children[i] = NULL;
			}


		}
		if(root->count)
					{
					printf("%s%c\t%d\n",root->word,root->letter,root->count);
					free(root);
					}
	}

}

// This methods work on a Valid word ONLY!
int updateWordInTrie(node* root , char* word)
{
	int wordLength = 0;
	char currentLetter  = word[wordLength];
	node* currentNode = root;
	// Init children index
	int letterIndex = currentLetter - 'a';
	// At this point there is a Child to our Root.

	while(true)
		
	{
		// If the next char is not a letter


		if (currentNode->children[letterIndex] == NULL)
		{
			// Create if not exist.
			currentNode->children[letterIndex] = getNewChildNode(currentNode ,currentLetter);
		}
		if (!IsCharacter(word[wordLength + 1]))
		{
			// That means the word is ended
			currentNode = currentNode->children[letterIndex]; // Set current Node to be his proper child
			wordLength++;
			currentNode->count++;
			
			return wordLength;
		}

		else{
			currentNode = currentNode->children[letterIndex]; // Set current Node to be his proper child
			wordLength++;
			currentLetter = word[wordLength];
			letterIndex = currentLetter - 'a';
		}
	}


	return wordLength;
}

node* initTrieRoot()
{
    node* root = malloc(sizeof(node)); 
    root->count = 0;
    root->word = "";
    root->letter = '\0';
    int i; // for Now the RootLetter is @
    // Set all children to NULL
	for (i = 0; i < NUM_LETTERS; i++)
		root->children[i] = NULL;

    return root;
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
    newWord[fWordLen] = father->letter;
    newWord[fWordLen+1] = '\0';

    Node->word = newWord;

    // Set Letter;
    Node->letter = currentLetter;
    return Node;

}

node* PreParringTheText(char* word ,node* root)
{
	int next_Word_Length = 0;
    int i = 0;
    //char a = 'abc';
   // printf("this is the word :%s\n" , word);
    int size = (textSize(word));
    //printf(" the size is : %d\n", size);
    word = Decapitalize(word,size);
    //we can work after this!!!!!!!!!!!!!!
   // printf(" im here %s\n",lower);
    //node* root = initTrieRoot();
    while(i<size)
    {

    next_Word_Length = nextWordLength(&word[i]);
    char* currentWord = calloc(next_Word_Length+1,sizeof(char)); //chacnge word to lower
    currentWord = wordString(&word[i]);
    currentWord[next_Word_Length] = '\0';
    updateWordInTrie(root , currentWord);
    i=i+next_Word_Length+1;
    free(currentWord);
    }
    free(word);
    return root;

   // printf(" the size if this Word is :%d " , size);
   // printf("This is sparta\n");
    //printf("%s\n" , word);

}

bool IsCharacter(char a)
{
    return ((a >= 'a') && (a <= 'z'));
}
bool isCapital(char a)
{
    return((a >= 'A') && (a <= 'Z'));
}

char* Decapitalize(char* input,int sizeOfInput)
{
    int i ;
    int DIST = 'a' - 'A';
    int sizeOfChar = sizeof(char);
    char* newword = calloc(sizeOfInput,sizeOfChar);
    for(i=0;i<sizeOfInput; i++)
    {
        if(isCapital(input[i]))
        {
            newword[i] = (char)((int)(input[i])+DIST);   
        }
        else
        {
             newword[i] = input[i];
        }
    }
       
   // printf(" After decapitalization : %s\n",newword);

   // printf("\nTest Print %s\n",input);
    return newword;


}


// Work only with lowercase letters , so decapitalize is necessery
int textSize(char*text)
{
    int sizeOfText = 0;
    while(text[sizeOfText] != '\0')
    {
        sizeOfText++;
    }
    return sizeOfText; 
}
int nextWordLength(char* wordStart)
{
    // If the Word is empty, return
    if (wordStart[0] == '\0')
    {
        return 1; /// Might BE WRONG
    }
   int wordLengthCounter = 0;
    // Finding the length of the Word
    while(IsCharacter(wordStart[wordLengthCounter]))
    {
        wordLengthCounter++;
    }
    return wordLengthCounter;     
}
// This methods extracts a word from a text 
char* wordString(char* startOfWord )
{ 
    int sizeOfWord = nextWordLength(startOfWord);
    char* theWord = malloc(sizeof(char)*sizeOfWord);
    memcpy(theWord,startOfWord , sizeOfWord);
    return theWord;
}



