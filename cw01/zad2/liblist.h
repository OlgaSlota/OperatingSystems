/* 
 * File:   library.h
 * Author: Słota Olga
 
 */

#ifndef LIBLIST_H_
#define LIBLIST_H_


typedef struct node node;
typedef struct person person;

struct person {
        char name[20];
	char lastname[20];
	char born[10];
	char email[40];
	char phone[10];
	char address[40];
       
};

struct node {    
        person * p;
	node * next;
	node * previous;
};


node * create_list(void);
void destroy(node ** head);
node * sort (node * head);
void insert(node ** head, person* per );
node * search ( node * head ,char * name, char*  lastname);
void rem(node ** head , person * per);
person * create_person(char name[], char lastname[] , char born[] , char email[] , char phone[] , char address[]);
node *split( node *head);
node *merge(node *first,  node *second);
node *mergeSort( node *head);
void print( node *head);
void print_helper(char tab[] , int size);
#endif
