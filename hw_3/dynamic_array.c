#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "arbitrary_array.h"

//#include "arbitrary_array.c"
/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/
static int count = 0;
static ArbitraryArray * arr = ArbitraryArray_new(sizeof(DynamicArray *));

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    ArbitraryArray_set_from_ptr(arr, count, &da);
    count ++;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    assert(da->buffer != NULL);
    
    for(int i = 0; i<count; i++) {
        DynamicArray ** arr_sth = (DynamicArray **) ArbitraryArray_get_ptr(arr,i); 
        
        if(*arr_sth == da) {
            
            for(int i = 0; i< count-1; i++) {
                DynamicArray ** temp = (DynamicArray **) ArbitraryArray_get_ptr(arr,i+1);
                ArbitraryArray_set_from_ptr(arr, i, temp);
            }
        }
        
    }
    
    free(da->buffer);
    da->buffer = NULL;
    count --;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value =  DynamicArray_first(da);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}
DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

    assert(da->buffer != NULL);

    if ( b < a ) {
        printf("DynamicArray_subarray called with invalid indices (b=%d<a%d)", b, a);
        exit(1);
    }

    DynamicArray * result = DynamicArray_new();

    for (int i=a; i<b; i++) {
        DynamicArray_push(result,DynamicArray_get(da, i));
    }

    return result;

}

//question 1
double DynamicArray_min(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double min = DynamicArray_get(da, 0);
    for (int i = 1; i< DynamicArray_size(da); i++) {
        if(min > DynamicArray_get(da, i)){
            min = DynamicArray_get(da, i);
        }
    }
    return min;

}
double DynamicArray_max(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double max = DynamicArray_get(da, 0);
    for (int i = 1; i< DynamicArray_size(da); i++) {
        if(max < DynamicArray_get(da, i)){
            max = DynamicArray_get(da, i);
        }
    }
    return max;
}
double DynamicArray_mean(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double mean;
    mean = DynamicArray_sum(da)/DynamicArray_size(da);
    return mean;
}

double DynamicArray_median(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    DynamicArray * b = DynamicArray_copy(da);
    double median;
    double temp;
    for(int i = 0; i<DynamicArray_size(b)-1; i++) {
        for(int j = i+1;j<DynamicArray_size(b); j++) {
            if(DynamicArray_get(b, j)<DynamicArray_get(b, i)){
                temp = DynamicArray_get(b, i);
                DynamicArray_set(b, i, DynamicArray_get(b, j));
                DynamicArray_set(b, j, temp);
            }
        }
    }
    

    if(DynamicArray_size(b)%2 == 0) {
        median = (DynamicArray_get(b, DynamicArray_size(b)/2) + 
                DynamicArray_get(b, DynamicArray_size(b)/2 -1))/2;
    } else {
        median =DynamicArray_get(b, DynamicArray_size(b)/2);
    }
    DynamicArray_destroy(b);
    return median;

}
double DynamicArray_sum(const DynamicArray * da){
    double sum = 0;
    if(DynamicArray_size(da)==0) {
        sum = 0;
    } else {
        for (int i = 0; i< DynamicArray_size(da); i++) {
            sum += DynamicArray_get(da, i);
        }
    }
    return sum;
}
//question 2
double DynamicArray_last(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, DynamicArray_size(da)-1);
}

double DynamicArray_first(const DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da, 0);
}

//question 3
DynamicArray * DynamicArray_copy (const DynamicArray * da ) {
    //printf("%d\n", 8888);
    DynamicArray * cp = DynamicArray_new(); 
    for(int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(cp, i, DynamicArray_get(da, i));
    }
    return cp;
}

//question 4
DynamicArray * DynamicArray_range( double a, double  b, double step){
    DynamicArray * t = DynamicArray_new();
    int size = (b-a)/step +1;
    for(int i = 0; i<size; i++) {
        DynamicArray_push(t, a+i*step);
    }
    return t;
}

//question 5
DynamicArray * DynamicArray_concat( const DynamicArray * a, const DynamicArray * b) {
    DynamicArray * c = DynamicArray_copy(a);
    for(int i = 0; i<DynamicArray_size(b); i++) {
        DynamicArray_set(c, i+ DynamicArray_size(a), DynamicArray_get(b, i));
    }
    return c;
}

//question 6
DynamicArray * DynamicArray_take(DynamicArray * a, int elemt) {
     DynamicArray * b = DynamicArray_new();
    if (elemt > 0) {
        if(elemt<=DynamicArray_size(a)) {
            for (int i = 0; i< elemt; i++) {
                DynamicArray_set(b,i, DynamicArray_get(a, i));
            }
        }else {
            for (int i = 0; i<DynamicArray_size(a); i++) {
                 DynamicArray_set(b,i, DynamicArray_get(a, i));
            }
            for(int i = DynamicArray_size(a); i< elemt; i++) {
                DynamicArray_set(b,i, 0);
            }
        }
    } else if (elemt < 0) {
        int token = abs(elemt);
        if(token<=DynamicArray_size(a)) {
            for(int i = 0; i<token; i++) {
                DynamicArray_set(b,i, DynamicArray_get(a, DynamicArray_size(a)-i-1));
            }
        } else {
            for(int i = 0; i<DynamicArray_size(a); i++) {
                DynamicArray_set(b,i, DynamicArray_get(a, DynamicArray_size(a)-i-1));
            }
            for (int i = DynamicArray_size(a); i< token; i++) {
                DynamicArray_set(b, i, 0);
            }
        }
    } else {
        return b;
    } 
    return b;
}

//question 8

int DynamicArray_num_arrays(){
    //return ArbitraryArray_size(arr);
    //printf("%d\n", count);
    //printf("%d\n",ArbitraryArray_size(arr));
    //assert(ArbitraryArray_size(arr) == count);
    return count;
    //return ArbitraryArray_size(arr);
}

int DynamicArray_destroy_all(){
    for(int i = 0; i<count; i++){
        
        //printf("I am here\n");
       //DynamicArray_to_string((DynamicArray *) ArbitraryArray_get_ptr(arr, i));
       DynamicArray ** arr_i = (DynamicArray **) ArbitraryArray_get_ptr(arr, i);
       free((*arr_i)->buffer);
       (*arr_i)->buffer=NULL;
        //DynamicArray_destroy(*arr_i);
       
       //DynamicArray_destroy((DynamicArray*) ArbitraryArray_get_ptr(arr, i));
        
        
        //DynamicArray_destroy(DynamicArray_get(arr, i));
        //ArbitraryArray_remove(arr, i);
    }
    
    count = 0;
    return count;
}

int DynamicArray_is_valid(const DynamicArray * da){
    if(da->buffer == NULL) {
        return 0;
    } else {
        return 1;
    }
}
