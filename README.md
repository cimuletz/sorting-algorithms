# Sorting Algorithms
## Implementation
### QuickSort
Implemented using median-of-three pivot, using InsertionSort when subarray length is smaller than 10 elements.
### RadixSort

Best base was found to be 256 (2^8), because it's 1/4 of sizeof(int). Also tested times for bases 2^10 and 2^16 (1/2 of sizeof(int), but uses a lot more memory).

| Size of input / Base | RadixSort256 | RadixSort1024 | RadixSort65536 |
| -------------------- | ------------ | ------------- | -------------- |
|`10^3 numbers range 1 - 10^3`|1.59e-05[s] | 1.76e-05[s] | 0.0002543[s] |
|`10^5 numbers range 1 - 10^5`|8.87e-05[s] | 0.0001004[s] | 0.0002016[s] |
|`10^6 numbers range 1 - 10^6`|0.0144816[s] | 0.0162262[s] | 0.0120301[s] |
|`10^8 numbers range 1 - 2*10^9`|1.84932[s] |2.31532[s] | 2.32628[s] |

 ### MergeSort
 Usual MergeSort algorithm with InsertionSort for subarray size smaller than 32.
 ### IntroSort
 Uses QuickSort until a certain recursion depth; MergeSort until subarray size is smaller than 32, then InsertionSort. Maximum recursion depth calculated as 2log(n), where n is size of array to be sorted. 
 ### TimSort
 Simplified version of TimSort (without optimizations such as galloping), with runs of 32 elements sorted using BinaryInsertionSort and runs sorted subsequently with MergeSort.
## Benchmarks
Algorithms tested on different array sizes with elements in different ranges picked randomly with mt19937. Special case with array already sorted in descending order.

| Size of input / Algorithm | STLSort | QuickSort | MergeSort | RadixSort | IntroSort | TimSort |
| ------------------------- | ------- | --------- | --------- | --------- | --------- | ------- |
|`10^3 numbers max 10^3`|2.97e-05[s] | 3.68e-05[s] | 0.0001042[s] | 8.5e-06[s] | 2.97e-05[s] | 8.91e-05[s]|
|`10^5 numbers max 10^5`|0.0003805[s] | 0.000892[s] | 0.0012323[s] | 6.82e-05[s] | 0.0004683[s] | 0.0011378[s] |
|`10^6 numbers max10^6`|0.004638[s] | 0.0065315[s] | 0.0120281[s] | 0.001198[s] | 0.0063249[s] | 0.0112485[s] |
|`10^7 numbers max 10^6`|0.610136[s] |0.716287[s] | 1.55429[s] | 0.129992[s] | 0.725209[s] | 1.42393[s]|
|`10^8 numbers max 2*10^9`|7.1875[s] |8.61952[s] | 16.7551[s] | 1.98521[s] | 8.8077[s] | 16.4081[s]|
|`10^7 decreasing numbers max 10^7`|0.094519[s] |0.479873[s] | 0.7497[s] | 1.01885[s] | 0.712219[s] | 0.780185[s]|

Conclusions:
* RadixSort clearly has the lowest average time
* QuickSort and IntroSort get pretty close to standard sort in C++
* TimSort is drawn back by simple implementation and the lack of optimizations
* MergeSort is drawn back by the use of extra memory, could be avoided by using tricks to hold two values in one memory space for arrays with low values
