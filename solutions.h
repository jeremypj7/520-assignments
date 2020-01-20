#ifndef SOLUTIONS_H
#define SOLUTIONS_H

//question 1
int running_total ( int a );

//question 2
int * reverse_in_place ( int a[], int length) ;

//question 3
int * reverse (int a[], int length);

//question 4
int num_instances(int a[], int length, int value);

//question 5
int * to_set (int a[], int length, int * n) ;

//question 6
typedef struct {
    double x, y, z;
} Point;

Point * map (Point a[], int length, Point (*funct)(Point));


//question 7
//create single linked list
/*
typedef struct node{
    double data;
    struct node * next;
} node_str;

//define stack
typedef struct {
    node_str *head;
    int size;
}stack_str;
*/

typedef enum status{ NOT_INITIALIZED_ERROR, OK, POP_ERROR, 
                     NEGATE_ERROR, MULT_ERROR, ADD_ERROR, OVERFLOW_ERROR
 }Status;

void rpn_init();

void rpn_push(double value);

double rpn_pop();

void rpn_negate();

void rpn_add();

void rpn_multiply();

void rpn_free();

Status rpn_error();

//void rpn_print();




#endif