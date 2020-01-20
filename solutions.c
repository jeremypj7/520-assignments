#include "solutions.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
/*
/question 1
/fn called running_total
/keeps track of the sum of the arguments it has been called with over time
*/
int running_total(int num) {
    static int sum = 0;
    sum += num;
    return sum;  
}

/*
/question 2
/fn called reverse_in_place
/takes an array and its length and reverses it in place
*/
int * reverse_in_place(int a[], int length) {
    int start = 0;
    int end = length -1;
    while  (start < end) {
        int temp = a[start];
        a[start]=a[end];
        a[end]=temp;
        start++;
        end--;
    }
    return a;
}

/*
/question 3
/fn called reverse
/takes an array and its length and returns a new array
/new array is the reverse of the given array
*/
int * reverse(int a[], int length) {
    int * b = (int *) calloc(length, sizeof(int));
    for(int i =0; i<length; i++) {
        b[i] = a[length-i-1];
    }
    return b;
}

/*
/question 4
/fn  called num_instances
/takes an array of integers, a length, and a value 
/returns the number of instances of that value in the array.
*/
int num_instances(int a[], int length, int value) {
    int count = 0;
    for (int i = 0; i<length; i++) {
        if(a[i] == value) {
            count ++;
        }
    }
    return count;
}

/*
/question 5
/fn called to_set
/takes an array, its length, a pointer to an integer
/returns a new array with all duplicates removed
*/

int * to_set (int a[], int length, int * n) {
    int * b = (int *) calloc(length, sizeof(int)); 
    int size = 0;
    for(int i = 0; i < length; i++) {
        bool found = false;
        for (int j = 0; j < size; j++) {
            if (b[j] == a[i]) {
                found = true;
            }
        }
        if (!found) {
            b[size] = a[i];
            size++;
        }
    }
    
    *n = size;
    return b;
}


/*
/question 6
/fn called map
/takes an array of Points, its length, and a function pointer
/returns a newly allocated array 
/whose values are the values of the function argument applied to 
/the array argument.
*/

Point * map(Point a[], int length, Point (*funct)(Point)) {
    Point * b = (Point *) malloc(length*sizeof(Point));
    for (int i = 0; i<length; i++) {
        b[i] = funct(a[i]);
    }  
    return b;
}

/*
/question 7
/Write a reverse polish notation (RPN) calculator in C 
/with functions rpn_init, rpn_push, rpn_add, rpn_negate, rpn_multiply, rpn_pop, rpn_error
*/

static int size_init = 100;
static int top = 0;
static Status err = NOT_INITIALIZED_ERROR;
static double * ptr; 

void rpn_init(){
    ptr = (double *) calloc(size_init,sizeof(double));
    err = OK;
}

void rpn_push(double value){
    if(top >= 100) {
        size_init = 2* size_init;
        ptr = (double *) realloc(ptr, size_init*sizeof(double));
    }
    if(value > DBL_MAX) {
        err = OVERFLOW_ERROR;
    } else{
        
        ptr[top] = value; 
        top++;
    }
}

double rpn_pop(){
    if(err == OVERFLOW_ERROR) {
        return 0;
    }
    if(top == 0) {
        //  POP_ERROR
        err = POP_ERROR;
        return 0;
    } else {
        top--;
        double temp = ptr[top];
        return temp;
    }
}

void rpn_negate(){ 
    if(err != NOT_INITIALIZED_ERROR) {
        if(top <= 0) {
            //  NEGATE_ERROR
            err = NEGATE_ERROR;
            
        } else {
            double temp = -rpn_pop();
            rpn_push(temp);
        }
    }
}

void rpn_add(){
    //printf("%d", top);
    if(err != NOT_INITIALIZED_ERROR) {
        if(top <= 1) {
            // ADD_ERROR
            err = ADD_ERROR;
        } else {
            double a = rpn_pop();
            double b = rpn_pop();
            double x = a+b;

            // catch a NaN
            if (x > DBL_MAX) {
                err = OVERFLOW_ERROR;
                return;
            } else {
                rpn_push(x);
            }
            //printf("%d/n", top);
        }
    }
}

void rpn_multiply(){
    if(err != NOT_INITIALIZED_ERROR) {
        if(top <= 1) {
            // MULT_ERROR
            err =MULT_ERROR;
            
        } else {
            double a = rpn_pop();
            double b = rpn_pop();
            double x = a*b;

            // catch a NaN
            if (x > DBL_MAX) {
                err = OVERFLOW_ERROR;
                return;
            } else {
                rpn_push(x);
            }

            
        }
    }
}

void rpn_free(){
    free(ptr);
    //uninitialize
    top = 0;
    //ptr = NULL;
    err = NOT_INITIALIZED_ERROR;
}

Status rpn_error(){
    return err;
}


