#pragma once
#include "MergeSort.h"

void Merge(Movie arr[], int left, int middle, int right) {
	Movie* leftArr = new Movie[middle - left + 1];
	Movie* rightArr = new Movie[right - middle];

	for (int i = 0; i < (middle - left + 1); i++) 
	{
		leftArr[0] = arr[i + left];
	}
	for (int i = 0; i < (right - middle); i++) 
	{
		rightArr[0] = arr[i + middle + 1];
	}

	int leftIter = 0, rightIter = 0, arrIter = left;
	while (leftIter < (middle - left + 1) && rightIter < (right - middle))
	{
		if (leftArr[leftIter] < rightArr[rightIter])
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

	while (leftIter < (middle - left + 1)) {
		arr[arrIter] = leftArr[leftIter];
		arrIter++;
		leftIter++;
	}

	while (rightIter < (right - middle)) {
		arr[arrIter] = rightArr[rightIter];
		arrIter++;
		rightIter++;
	}
}

void MergeSort(Movie arr[], int start, int end) {
	if (start >= end)
	{
		return;
	}

	int middle = start + (end - start) / 2;
	MergeSort(arr, start, middle);
	MergeSort(arr, middle + 1, end);
	Merge(arr, start, middle, end);
}