# Bucket Sort

A C implementation of bucket sort for alphabetically sorting strings using dynamically allocated linked lists.

This project was developed as a Systems Programming assignment at Florida International University. It demonstrates the use of C structures, pointers, linked lists, dynamic memory allocation, command-line arguments, and string processing.

## Overview

The program reads a series of space-separated strings from standard input and distributes them among a set of alphabetically defined buckets.

Each bucket contains a singly linked list that remains sorted as new words are inserted. After all input has been processed, the program prints each non-empty bucket and its sorted contents.

String comparisons are case-insensitive.

## Data Structures

The program uses two C structures to organize the data.

### Node

Each node stores a dynamically allocated string and a pointer to the next node in the linked list:

```c
typedef struct node {
    char* string;
    struct node* next;
} node;
```

### Bucket

Each bucket stores its minimum alphabetical boundary and the head of its linked list:

```c
typedef struct bucket {
    char* min_word;
    node* head;
} bucket;
```

Together, these structures allow the program to maintain an array of buckets containing individually sorted linked lists.

## Bucket Creation

Bucket boundaries are supplied through command-line arguments.

For example:

```bash
./bucketsort h p
```

creates three buckets:

```text
Bucket 0: words before "h"
Bucket 1: words from "h" up to "p"
Bucket 2: words from "p" onward
```

The command-line boundaries must be supplied in alphabetical order.

## Sorting

For each word read from standard input, the program:

1. Determines the appropriate bucket based on the bucket boundaries.
2. Dynamically allocates a new linked-list node.
3. Copies the word into dynamically allocated memory.
4. Inserts the node into the correct position in the bucket's linked list.
5. Keeps the contents of each bucket alphabetically sorted.

Case-insensitive comparisons are performed using `strcasecmp()`.

## Building the Project

Compile the program using GCC:

```bash
gcc -Wall -Wextra -o bucketsort bucketsort.c
```

## Running the Program

Provide alphabetically ordered bucket boundaries as command-line arguments and supply the words through standard input.

For example:

```bash
echo "apple zebra mango banana kiwi orange grape" | ./bucketsort h p
```

Output:

```text
bucket 0: apple banana grape
bucket 1: kiwi mango orange
bucket 2: zebra
```

The program only displays non-empty buckets.

## Input Validation

The program checks that:

- At least one bucket boundary is provided.
- Bucket boundaries are supplied in alphabetical order.

If the boundaries are not alphabetically sorted, the program terminates with an error.

## Memory Management

Memory is dynamically allocated for:

- The bucket array
- Bucket boundary strings
- Linked-list nodes
- Strings stored within each node
- The input buffer

Before the program exits, dynamically allocated memory is released.

## Project Structure

```text
bucket-sort/
├── README.md
├── bucketsort.c
└── .gitignore
```

## Concepts Demonstrated

- C programming
- Bucket sort
- Insertion-based sorting
- Singly linked lists
- Structures
- Pointers
- Dynamic memory allocation
- String manipulation
- Command-line arguments
- Standard input
- Case-insensitive string comparison
- Memory management

## What I Learned

This assignment provided experience implementing a sorting algorithm using custom data structures in C.

I gained hands-on experience using structures and pointers to construct linked lists, dynamically allocating memory for strings and nodes, processing command-line arguments, and organizing data into buckets based on alphabetical boundaries.

Maintaining each linked list in sorted order also demonstrated how insertion-based sorting can be incorporated directly into a data structure as new elements are added.