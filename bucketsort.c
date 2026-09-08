/*
 * gcc -Wall -Wextra -o bucketsort bucketsort.c
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10000
#define error(message, code) do { printf("%s\n", message); exit(code); } while(0)

typedef struct node {
    char* string;
    struct node* next;
} node;

typedef struct bucket {
    char* min_word;
    node* head;
} bucket;

void insert_sorted(node** head, char* word) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->string = strdup(word);
    new_node->next = NULL;

    if (*head == NULL || strcasecmp(word, (*head)->string) < 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    node* current = *head;
    while (current->next != NULL && strcasecmp(word, current->next->string) >= 0) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

int find_bucket_index(bucket* buckets, int size, char* word) {
    for (int i = 1; i < size; i++) {
        if (strcasecmp(word, buckets[i].min_word) < 0)
            return i - 1;
    }
    return size - 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        error("bucketsort: Not enough arguments.", 1);

    int num_buckets = argc;
    bucket* buckets = (bucket*)malloc(num_buckets * sizeof(bucket));
    buckets[0].min_word = strdup("");
    buckets[0].head = NULL;

    for (int i = 1; i < argc; i++) {
        buckets[i].min_word = strdup(argv[i]);
        buckets[i].head = NULL;
        if (strcasecmp(buckets[i - 1].min_word, buckets[i].min_word) >= 0)
            error("bucketsort: Must be alphabetically sorted.", 1);
    }

    char* line = (char*)malloc(MAX_LEN);
    while (fgets(line, MAX_LEN, stdin)) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        char* word = strtok(line, " ");
        while (word != NULL) {
            int index = find_bucket_index(buckets, num_buckets, word);
            insert_sorted(&buckets[index].head, word);
            word = strtok(NULL, " ");
        }
    }

    for (int i = 0; i < num_buckets; i++) {
        if (buckets[i].head != NULL) {
            printf("bucket %d:", i);
            node* current = buckets[i].head;
            while (current != NULL) {
                printf(" %s", current->string);
                current = current->next;
            }
            printf("\n");
        }
    }

    // Free memory
    for (int i = 0; i < num_buckets; i++) {
        node* current = buckets[i].head;
        while (current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp->string);
            free(temp);
        }
        free(buckets[i].min_word);
    }
    free(buckets);
    free(line);

    return 0;
}
