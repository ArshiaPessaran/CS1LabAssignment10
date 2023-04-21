#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *children[26];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *curr = *ppTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = (struct Trie *) calloc(1, sizeof(struct Trie));
        }
        curr = curr->children[index];
    }
    curr->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *curr = pTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    struct Trie *trie = (struct Trie *) calloc(1, sizeof(struct Trie));
    char *words[] = {"notaword", "ucf", "no", "note", "corg"};
    int numWords = sizeof(words) / sizeof(words[0]);
    for (int i = 0; i < numWords; i++) {
        insert(&trie, words[i]);
    }
    for (int i = 0; i < numWords; i++) {
        printf("\t%s : %d\n", words[i], numberOfOccurrences(trie, words[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
