#include <iostream>
#include <list>
#include <functional>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>
#include <time.h>

int user_main(int argc, char **argv);

/* Demonstration on how to pass lambda as parameter.
 * "&&" means r-value reference. You may read about it online.
 */
void demonstration(std::function<void()> && lambda) {
	lambda();
}

typedef struct{
	int low;
	int high;
	std::function<void(int)> lambda;
} thread_args;

typedef struct {
    int low1;
    int high1;
    int low2;
    int high2;
    std::function<void(int, int)> lambda;
} thread_args_2D;

void* thread_func(void* ptr){
	thread_args* t = (thread_args*) ptr;

	for(int i = t->low;i<t->high;i++){
		t->lambda(i);
	}

	return NULL;
}

void* thread_func_2d(void* ptr) {
    thread_args_2D* t = (thread_args_2D*)ptr;

    for (int i = t->low1; i < t->high1; i++) {
        for (int j = t->low2; j < t->high2; j++) {
            t->lambda(i,j);
        }
    }

    return NULL;
}

void parallel_for(int low, int high, std::function<void(int)> &&lambda, int numThreads){
	clock_t start = clock();
	
	pthread_t threads[numThreads];
	thread_args arguments[numThreads];
	
	int range = high - low;
    int chunk = (range + numThreads - 1) / numThreads;

	for (int t = 0; t < numThreads; t++) {
        int start = low + t * chunk;
        int end = std::min(start + chunk, high);

        if (start >= high) break; // No work for this thread

        // Initialize arguments
        arguments[t].low = start;
        arguments[t].high = end;
        arguments[t].lambda = lambda;

        // Create thread
        pthread_create(&threads[t], NULL, thread_func, &arguments[t]);
    }

	 // Join all threads
    for (int t = 0; t < numThreads; t++) {
        pthread_join(threads[t], NULL);
    }

	clock_t end = clock();

    // Calculate elapsed time in seconds
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Total execution time: %f seconds\n", time_taken);

	return;
}

void parallel_for(int low1, int high1, int low2, int high2,std::function<void(int, int)> &&lambda, int numThreads){
	clock_t start = clock();
	
	pthread_t threads[numThreads];
    thread_args_2D arguments[numThreads];

    int range1 = high1 - low1; // Range of the outer loop
    int chunk1 = (range1 + numThreads - 1) / numThreads; // Divide outer loop into chunks

    for (int t = 0; t < numThreads; t++) {
        int start1 = low1 + t * chunk1;
        int end1 = std::min(start1 + chunk1, high1);

        if (start1 >= high1) break; // No work for this thread

        // Initialize thread arguments
        arguments[t].low1 = start1;
        arguments[t].high1 = end1;
        arguments[t].low2 = low2; // Inner loop range remains the same
        arguments[t].high2 = high2;
        arguments[t].lambda = lambda;

        // Create thread
        pthread_create(&threads[t], NULL, thread_func_2d, &arguments[t]);
    }

    // Join threads
    for (int t = 0; t < numThreads; t++) {
        pthread_join(threads[t], NULL);
    }

	clock_t end = clock();

    // Calculate elapsed time in seconds
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Total execution time: %f seconds\n", time_taken);

	return;
}

int main(int argc, char **argv) {
	/* 
	* Declaration of a sample C++ lambda function
	* that captures variable 'x' by value and 'y'
	* by reference. Global variables are by default
	* captured by reference and are not to be supplied
	* in the capture list. Only local variables must be 
	* explicity captured if they are used inside lambda.
	*/
	int x=5,y=1;
	// Declaring a lambda expression that accepts void type parameter
	auto /*name*/ lambda1 = /*capture list*/[/*by value*/ x, /*by reference*/ &y](void) {
	/* Any changes to 'x' will throw compilation error as x is captured by value */
	y = 5;
	std::cout<<"====== Welcome to Assignment-"<<y<<" of the CSE231(A) ======\n";
	/* you can have any number of statements inside this lambda body */
	};
	// Executing the lambda function
	demonstration(lambda1); // the value of x is still 5, but the value of y is now 5

	int rc = user_main(argc, argv);

	auto /*name*/ lambda2 = [/*nothing captured*/]() {
	std::cout<<"====== Hope you enjoyed CSE231(A) ======\n";
	/* you can have any number of statements inside this lambda body */
	};
	demonstration(lambda2);
	return rc;
}

#define main user_main


