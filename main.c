#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define NUM_LETTERS (26) 
// typedef enum {FALSE = 0, TRUE = 1} boolean; 

// Headers////
bool isCapital(char a);
bool IsCharacter(char a);
//node* getNewChildNode(node* father ,char currentLetter);
//node* initTrieRoot();
void Decapitalize(char* input ,int sizeOfInput);

char* wordString(char* startOfWord);
//void InitTreeByText(node* root, char* text);
int textSize(char*text);


int main()
{
    int i = 0 ;
    char* word = "SARRAH SHARA SHIR SAMEH";
    printf("this is the word :%s\n" , word);
    int size = textSize(word);
    //printf(" the size is : %d\n", size);

    Decapitalize(word,size);
    char* currentWord = malloc(nextWordLength(word)*sizeof(char));
    currentWord = wordString(word);
    printf("\nthe String is : %s\n",currentWord);
    

   // printf(" the size if this Word is :%d " , size);
   // printf("This is sparta\n");
    //printf("%s\n" , word);
    return 0 ;
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
    
    char* newword = malloc(sizeof(char)*sizeOfInput);
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
       
    printf("%s\n",newword);

    return 0;
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
    if (*wordStart == '\0')
    {
        return 0;
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
char* wordString(char* startOfWord)
{ 
    printf("line99");  
    int sizeOfWord = nextWordLength(startOfWord);
printf("line100 sizeofWorf is :%d" , sizeOfWord);
    char* theWord = malloc(sizeof(char)*sizeOfWord);
printf("line102");    
    memcpy(theWord,startOfWord , sizeOfWord);
printf("line104");
    return theWord;
}



