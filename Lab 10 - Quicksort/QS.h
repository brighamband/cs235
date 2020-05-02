#ifndef QS_H_
#define QS_H_

#include "QSInterface.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

template<typename T>
class QS : public QSInterface<T> {
private:
	int* qsArray;
	size_t arraySize;
	size_t arrayCapacity;
public:
	QS() {
		qsArray = NULL;
		arraySize = 0;
		arrayCapacity = 0;
	}
	~QS() { delete[] qsArray; }

	/** Dynamically allocate an initial array to the QuickSort class. */
	bool createArray(size_t capacity) {
		if (qsArray != NULL) {
			delete[] qsArray;
		}
		this->arrayCapacity = capacity;
		qsArray = new int[capacity];
		arraySize = 0;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	bool addElement(T element) {
		// add new element
		qsArray[arraySize] = element;
		arraySize++;
		// if the array size equals the capacity, double array capacity then dynamically allocate new array
		if (arraySize == arrayCapacity) {
			arrayCapacity = arrayCapacity * 2;
			int* tempArray = new int[arrayCapacity];
			// copy over current elements to temp array
			for (unsigned int i = 0; i < arraySize; ++i) {
				tempArray[i] = qsArray[i];
			}
			// free up memory from original array
			delete[] qsArray;
			// set pointer to the new array
			qsArray = tempArray;
		}
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	bool sort(size_t left, size_t right) { 
		if (right - left > 1) {
			// set pivot equal to the median of the subarray endpoints
			size_t pivot = 0;
			pivot = partition(left, right, medianOfThree(left, right));
			// sort left half
			sort(left, pivot);
			// sort right half
			sort(pivot + 1, right);
		}
		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	bool sortAll() { return sort(0, arraySize); }

	/** Removes all items from the QuickSort array. */
	bool clear() {
		arraySize = 0;
		return true;
	}

	/** Return size of the QuickSort array. */
	size_t capacity() const { return arrayCapacity; }

	/** Return number of elements in the QuickSort array. */
	size_t size() const { return arraySize; }

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	int medianOfThree(size_t left, size_t right) { 
		// return -1 if the array is empty
		if (arraySize == 0) return -1;
		// return -1 if either of the given integers is out of bounds
		if (left < 0 || right > arraySize) return -1;
		// return -1 if the left index is not less than the right index
		if (left >= right) return -1;
		// set middle index
		size_t middle = 0;
		middle = (left + right) / 2;
		// bubble-sort the values at the left, middle, and right indices
		int temp = 0;
		// if left is greater than right, switch positions
		if (qsArray[left] > qsArray[right - 1]) {
			temp = qsArray[left];
			qsArray[left] = qsArray[right - 1];
			qsArray[right - 1] = temp;
		}
		// if left is greater than middle, switch positions
		if (qsArray[left] > qsArray[middle]) {
			temp = qsArray[left];
			qsArray[left] = qsArray[middle];
			qsArray[middle] = temp;
		}
		// if middle is greater than right, switch positions
		if (qsArray[middle] > qsArray[right - 1]) {
			temp = qsArray[middle];
			qsArray[middle] = qsArray[right - 1];
			qsArray[right - 1] = temp;
		}
		return middle;
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
					2) if any of the given indexes are out of bounds,
					3) if the left index is not less than the right index.
	*/
	int partition(size_t left, size_t right, size_t pivotIndex) {
		// return -1 if the array is empty
		if (arraySize == 0) return -1;
		// return -1 if either of the given integers is out of bounds
		if (left < 0 || right > arraySize) return -1;
		// return -1 if the left index is not less than the right index
		if (left >= right) return -1;
		// return -1 if pivot is out of bounds
		if (pivotIndex < left || pivotIndex > right) return -1;

		// Move the median value to the first position (the pivot value) by exchanging table[first] and table[middle].
		size_t temp = qsArray[left];
		qsArray[left] = qsArray[pivotIndex];
		qsArray[pivotIndex] = temp;

		// Initialize up to first + 1 and down to last - 1.
		size_t up = left + 1;
		size_t down = right - 1;

		do {
			// Increment up until up selects the first element greater than the pivot value or up has reached last - 1.
			while ((up != right - 1) && !(qsArray[left] < qsArray[up])) ++up;
			// Decrement down until down selects the first element less than or equal to the pivot value or down has reached first.
			while (qsArray[left] < qsArray[down]) --down;
			// if up is to the left of down, exchange array[up] and array[down].
			if (up < down) {
				size_t temp = qsArray[up];
				qsArray[up] = qsArray[down];
				qsArray[down] = temp;
			}
		} while (up < down);
		// exchange array[left] and array[down], thus putting the pivot value in correct spot
		temp = qsArray[left];
		qsArray[left] = qsArray[down];
		qsArray[down] = temp;

		return down;		
	}

	/** @return: comma delimited string representation of the array. */
	string toString() const {
		stringstream ss;
		ss << qsArray[0];
		for (unsigned int i = 1; i < arraySize; ++i) {
			ss << "," << qsArray[i];
		}
		return ss.str();
	}

	friend ostream& operator<< (ostream& os, QS<T>& qs) {
		os << qs.toString();
		return os;
	}
};

#endif /* QS_H_ */