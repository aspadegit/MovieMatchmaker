#pragma once
#include "MergeSort.h"

void Merge(Movie arr[], int left, int middle, int right) {
	if (left >= right || middle > right) {
		return;
	}
	Movie *leftArr = new Movie[middle - left + 1];
	Movie *rightArr = new Movie[right - middle];

	for (int i = 0; i < (middle - left  + 1); i++)
	{
		leftArr[i] = arr[i + left];
	}
	for (int i = 0; i < (right - middle) && i + middle + 1 < right; i++)
	{
		rightArr[i] = arr[i + middle + 1];
	}

	int leftIter = 0, rightIter = 0, arrIter = left;
	while (leftIter < (middle - left + 1 ) && rightIter < (right - middle) && arrIter < right)
	{
		if (leftArr[leftIter] > rightArr[rightIter])
		{
			arr[arrIter] = leftArr[leftIter];
			leftIter++;
		}
		else
		{
			arr[arrIter] = rightArr[rightIter];
			rightIter++;
		}
		arrIter++;
	}

	
	while (leftIter < (middle - left + 1) && arrIter < right) {
		arr[arrIter] = leftArr[leftIter];
		arrIter++;
		leftIter++;
	}

	while (rightIter < (right - middle) && arrIter < right) {
		arr[arrIter] = rightArr[rightIter];
		arrIter++;
		rightIter++;
	}
	
	delete[] leftArr;
	delete[] rightArr;
}

void MergeSort(Movie arr[], int start, int end) {
	if (start >= end)
	{
		return;
	}

	int middle = start + ((end - start) / 2);
	MergeSort(arr, start, middle);
	MergeSort(arr, middle + 1, end);
	Merge(arr, start, middle, end);
}