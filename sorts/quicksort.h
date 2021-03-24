#pragma once

template <typename T>
void swap_(T* a, T* b) {
	T temp = *a;

	*a = *b;
	*b = temp;
}

int partition(long* data, int lo, int hi) {
	int last = lo - 1;
	int index = lo;
	int pivot = hi;

	while (index <= hi) {
		if (data[index] < data[pivot]) {
			last++;
			swap_(&data[last], &data[index]);
		}
		index++;
	}

	last++;
	swap_(&data[last], &data[pivot]);
	return last;
}

void quicksort_iter_(long* data, int lo, int hi) {
	if (lo >= hi)
		return;

	const int pivot = partition(data, lo, hi);

	quicksort_iter_(data, lo, pivot - 1);
	quicksort_iter_(data, pivot + 1, hi);
}

void quicksort_iter(long* data, int n) {
    quicksort_iter_(data, 0, n - 1);
}

void quicksort_par_(long* data, int lo, int hi) {
	if (lo >= hi)
		return;

	const int pivot = partition(data, lo, hi);

    #pragma omp task 
	quicksort_par_(data, lo, pivot - 1);

	#pragma omp task 
	quicksort_par_(data, pivot + 1, hi);
}

void quicksort_par(long* data, int n) {
    quicksort_par_(data, 0, n - 1);
}