#include <iostream>
#include <fstream>
#include <chrono> 
#include <string.h>

#include "omp.h"
#include "merge_sort.h"
#include "quicksort.h"

long* read_array(char *filename, int &size) {
    std::ifstream input;

    input.open(filename);
    if (input.is_open()) {
        input >> size;

        long* data = new long[size];

        for (int i = 0; i < size; i++) {
            input >> data[i];
        }

        return data;
    }

    size = -1;
    return nullptr;
}

void print_array(long *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// ./sorts.out thread_count filename
int main(int argc, char **argv) {
    int num_threads = 0;
    char filepath[100];

    sprintf(filepath, "%s", argv[2]);
    printf("Testfile path: %s\n", filepath);
    printf("Sorting algortihm used: %s\n", argv[3]);

    #ifdef _OPENMP
        sscanf(argv[1], "%d", &num_threads);
        omp_set_num_threads(num_threads);
        printf("Using %d threads\n", omp_get_max_threads());
    #endif

    int n = 0;
    long* data = read_array(filepath, n);

    if (n == 0) {
        printf("Dataset file not found\n");
        return 1;
    }

    printf("Dataset size: %d\n", n);
    auto start = std::chrono::high_resolution_clock::now(); 


    if (strcmp(argv[3], "merge_sort_iter") == 0) {
        merge_sort_iter(data, n);
    }
    else if (strcmp(argv[3], "merge_sort_par") == 0) {
        merge_sort_par(data, n);
    }
    else if (strcmp(argv[3], "quicksort_iter") == 0) {
        quicksort_iter(data, n);
    }
    else if (strcmp(argv[3], "quicksort_par") == 0) {
        quicksort_par(data, n);
    }
    else {
        printf("Sorting algorithm not found.\n");
        return 2;
    }

    auto end = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 

    std::cout << "Elapsed time: " << duration.count() << " microseconds" << std::endl; 

    // debug argument
    if (argc == 5 && strcmp(argv[4], "print") == 0) {
        print_array(data, n);
    }

    delete data;

    return 0;
}