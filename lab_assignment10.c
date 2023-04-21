#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    int count;
    struct TrieNode *children[26];
};

void insert(struct TrieNode **ppTrie, char *word){
 struct TrieNode *pTrie = *ppTrie;
    if (pTrie == NULL)
    {
        pTrie = (struct TrieNode *) malloc(sizeof(struct TrieNode));
        if (pTrie != NULL)
        {
            pTrie->count = 0;
            memset(pTrie->children, 0, sizeof(pTrie->children));
            *ppTrie = pTrie;
        }
    }
    if (pTrie != NULL && *word != '\0')
    {
        int index = *word - 'a';
        insert(&pTrie->children[index], word + 1);
    }
    else if (pTrie != NULL)
    {
        pTrie->count++;
    }
}
int numberOfOccurances(struct TrieNode *pTrie, char *word){
    while (pTrie != NULL && *word != '\0')
    {
        int index = *word - 'a';
        pTrie = pTrie->children[index];
        word++;
    }
    return (pTrie != NULL) ? pTrie->count : 0;
}
struct TrieNode *deallocateTrie(struct TrieNode *pTrie){
 if (pTrie != NULL)
    {
        for (int i = 0; i < 26; i++)
        {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void)
{
struct TrieNode *trie = NULL;
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = sizeof(pWords) / sizeof(pWords[0]);
    for (int i = 0; i < numWords; i++)
    {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < numWords; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
