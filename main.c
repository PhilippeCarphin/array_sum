#include <stdio.h>
#include <stdlib.h>

int sum(int *start, int *end);
void print_array(int *start, int *end);

size_t size(int *start, int *end){
    return end - start;
}

/*******************************************************************************
 * Prints all the intermediate arrays and their sums
*******************************************************************************/
void examine_array(int *start, int *end)
{
    for(int *p = start; p < end; p++){
        print_array(start, p+1);
    }
}

/*******************************************************************************
 * Prints the array from start to end (exclusive)
*******************************************************************************/
void print_array(int *start, int *end)
{
    int sum = 0;
    for(int *p = start; p < end; p++){
        printf("%d,", *p);
        sum += *p;
    }
    printf(" : sum = %d, size = %lu\n", sum, size(start,end));
}


/*******************************************************************************
 * Returns the sum of an array from start to end inclusively
*******************************************************************************/
int sum(int *start, int *end)
{
    int s = 0;
    int *p = start;

    for(int *p = start; p <= end; p++){
        s += *p;
    }

    return s;
}

int *find_match(int to_match, int *start, int *end, int *seen_start);

void do_array(int *start, int *end)
{
    int current_sum = 0;
    int array_size = end - start;
    int seen[array_size];
    int current_seen_sum = 0;

    print_array(seen, seen + array_size);
    for(int *cursor = start, *q = seen; cursor < end; cursor++, q++){
        print_array(seen, seen + array_size);
        int *other = find_match(*cursor, cursor+1, end, q+1);
        if (current_sum - *cursor < 0){
            *other *= -1;
        } else {
            int *largest = NULL;
            int *smallest = NULL;
            if( *other > *cursor ){
                largest = other;
                smallest = cursor;
            } else {
                largest = cursor;
                smallest = other;
            }

            if( current_seen_sum >= 0 ){
                *largest *= -1;
            } else {
                *smallest *= -1;
            }
        }

        *q = 1;
        *(seen + (other - start) +1) = 1;

        current_sum += *cursor;
        current_seen_sum += *cursor + *other;
    }
}
#define SEEN 1
int *find_match(int to_match, int *start, int *end, int *seen_start)
{
    int *best_match = start;
    for(int *p = start, *q = seen_start; p < end; p++, q++){
        if ( *q == SEEN ){
            continue;
        }
        int best_difference = abs(to_match - *best_match);
        int current_difference = abs(to_match -*p);
        if( current_difference < best_difference ){
            best_match = p;
        }
    }

    return best_match;
}


int main(void){

    int input[] = {9, 4, 2, 8};

    examine_array(input+0, input+4);

    printf("==========================\n");
    do_array(input+0, input+4);
    examine_array(input+0, input+4);

    return 0;
}
