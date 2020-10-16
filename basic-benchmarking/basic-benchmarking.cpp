// Basic Benchmarking lab exercise
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

// Define the alias "the_clock" for the clock type we're going to use.
// (You can change this to make the code below use a different clock.)
typedef std::chrono::steady_clock the_clock;


// The size of the array
#define WIDTH 5000
#define HEIGHT 10000
constexpr int NUM_OF_ELEMENTS = 11;

float array[HEIGHT][WIDTH];
float times[NUM_OF_ELEMENTS];
int stackTop = -1;
float sum = 0;
float xVal = 0;
float yVal = 0;

void storeTime(float time);
void sortTimes();
void printArray(float (&array)[NUM_OF_ELEMENTS]);
float computeMedian(float(&array)[NUM_OF_ELEMENTS]);

int main(int argc, char *argv[])
{
	// Fill the array with data
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			array[y][x] = float(x + y);
		}
	}

	while (true)
	{
		// Start timing
		the_clock::time_point start = the_clock::now();

		// Do something that takes some time
		//sleep_for(milliseconds(303));

		// Sum the array index values.
		//float sum = 0;

		

		for (int y = 0; y < WIDTH; ++y)
		{
			for (int x = 0; x < HEIGHT; ++x)
			{
				sum += array[y][x];

				// Summing with outer loop (X), innner loop (Y), avg median timing = 306ms
				// Summing with outer loop (Y), innner loop (X), avg median timing = 190ms - faster due to how memory is accessed, arrays are stored in contiguous blocks.

				// Changed the WIDTH and HEIGHT to 500 x 1000, as it was taking far too long with the print statement.
				// No Debug printing, median avg ~ 3ms
				// Debug printing, median avg ~ 23078ms

				// Arr size 500 x 1000 time ~ 3ms
				// Arr size 1000 x 2000 time ~ 15ms
				// Arr size 2000 x 4000 time ~ 59ms
				// Arr size 400 x 8000 time ~ 228ms

				// x outer loop y inner - DEBUG MODE - Arr size 5000 x 10000 - time ~ 352ms
				// x outer loop y inner - RELEASE MODE - Arr size 5000 x 10000 - time ~ 109ms

				// DEBUG MODE printing sum - time ~ 361ms
				// DEBUG MODE not printing sum - time ~ 352ms
				// RELEASE MODE printing sum - time ~ 110ms
				// RELEASE MODE not printing sum - time ~ 0ms

				// timings with sum as a local variable DEBUG MODE and printing - time ~ 359ms
				// timings with sum as a global variable DEBUG MODE and printing - time ~ 357ms

				//std::cout << "Measuring the overhead of a debug printing statement\n";
			}
		}

		// Stop timing
		the_clock::time_point end = the_clock::now();

		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();
		std::cout << "Sum total of array = " << sum << '\n';
		cout << "It took " << time_taken << " ms.\n";

		storeTime(time_taken);

		if (stackTop == NUM_OF_ELEMENTS)
		{
			break;
		}
	}

	std::cout << '\n';
	printArray(times);
	std::cout << '\n';
	sortTimes();
	std::cout << '\n';
	printArray(times);
	std::cout << '\n';

	int median = computeMedian(times);
	std::cout << "\nThe median avg = " << median << '\n';

	return 0;
}

void storeTime(float time)
{
	++stackTop;

	if (stackTop == NUM_OF_ELEMENTS)
	{
		return;
	}

	times[stackTop] = time;
}

void sortTimes()
{
	std::sort(times, times + NUM_OF_ELEMENTS);
}

void printArray(float (&array)[NUM_OF_ELEMENTS])
{
	for (auto& time : array)
	{
		std::cout << time << ", ";
	}
}

float computeMedian(float(&array)[NUM_OF_ELEMENTS])
{
	// Check even or odd num of elements. STLL TO DO!

	return array[(NUM_OF_ELEMENTS - 1) / 2];
}