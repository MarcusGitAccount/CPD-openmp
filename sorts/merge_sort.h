#pragma once

long* lo_container = nullptr;
long* hi_container = nullptr;

void merge(long *data, int lo, int mid, int hi) {

    int n = mid - lo + 1;
    int m = hi - mid;

    for (int i = 0; i < n; i++) {
        lo_container[i] = data[i + lo];
    }
    
    for (int i = 0; i < m; i++) {
        hi_container[i] = data[i + mid + 1];
    }


    int i, j, k;


    i = j = 0;
    k = lo;

    while (i < n && j < m) {
        if (lo_container[i] <= hi_container[j]) {
            data[k++] = lo_container[i++];
        }
        else {
            data[k++] = hi_container[j++];
        }
    }

    while (i < n) {
        data[k++] = lo_container[i++];
    }

    while (j < m) {
        data[k++] = hi_container[j++];
    }

}

void merge_sort_iter_(long *data, int lo, int hi) {
    if (hi <= lo) {
        return;
    }

    int mid = lo + ((hi - lo) >> 1);

    merge_sort_iter_(data, lo, mid);
    merge_sort_iter_(data, mid + 1, hi);
    merge(data, lo, mid, hi);
}

void merge_sort_iter(long *data, int n) {
    lo_container = new long[n];
    hi_container = new long[n];

    merge_sort_iter_(data, 0, n - 1);

    delete lo_container;
    delete hi_container;
}

void merge_sort_par_(long *data, int lo, int hi) {
    if (hi <= lo) {
        return;
    }

    int mid = lo + ((hi - lo) >> 1);

    #pragma omp task shared(data)
    merge_sort_par_(data, lo, mid);

    #pragma omp task shared(data)
    merge_sort_par_(data, mid + 1, hi);
    
    #pragma omp taskwait
    merge(data, lo, mid, hi);
}

void merge_sort_par(long *data, int n) {
    lo_container = new long[n];
    hi_container = new long[n];

    #pragma omp parallel
    {
        // printf("Using %d threads\n", omp_get_num_threads());
        merge_sort_par_(data, 0, n - 1);
    }
    
    delete lo_container;
    delete hi_container;
}