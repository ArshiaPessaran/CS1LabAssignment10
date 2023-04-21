#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *children;
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *curr = *ppTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (curr->children == NULL) {
            curr->children = (struct Trie *) calloc(1, sizeof(struct Trie));
        }
        curr = curr->children + index;
    }
    curr->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *curr = pTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (curr->children == NULL) {
            return 0;
        }
        curr = curr->children + index;
    }
    return curr->count;
}

void deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        if (pTrie->children != NULL) {
            for (int i = 0; i < 26; i++) {
                deallocateTrie(pTrie->children + i);
            }
            free(pTrie->children);
        }
        free(pTrie);
    }
}

int main(void) {
    struct Trie *trie = (struct Trie *) calloc(1, sizeof(struct Trie));
    int numWords;
    scanf("%d", &numWords);
    for (int i = 0; i < numWords; i++) {
        char word[100];
        scanf("%s", word);
        insert(&trie, word);
    }
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    deallocateTrie(trie);
    return 0;
}

