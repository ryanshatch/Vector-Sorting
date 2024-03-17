/**
============================================================================
 Name        : Vector Sorting
 Author      : Ryan Hatch
 Version     : 1.0
 Copyright   : Copyright © 2017 SNHU COCE
 Description : Vector Sorting Algorithms
============================================================================
 */
#include <algorithm>
#include <iostream>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid
{
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;

	Bid()
	{
		amount = 0.0;
	}
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid)
{
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " <<
		bid.fund << endl;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid()
{
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath)
{
	cout << "Loading CSV file " << csvPath << endl;

	// Define a vector data structure to hold a collection of bids.
	vector<Bid> bids;

	// initialize the CSV Parser using the given path
	auto file = csv::Parser(csvPath);

	try
	{
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++)
		{
			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bids.push_back(bid);
		}
	}
	catch (csv::Error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return bids;
}

// FIX ME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 * @return The index of the pivot element after partitioning
 */
int partition(vector<Bid>& bids, int begin, int end)
{
	int pivotIndex = begin + (end - begin) / 2;
	Bid pivotValue = bids[pivotIndex];
	int i = begin - 1;
	int j = end + 1;
	while (true)
	{
		do
		{
			i++;
		}
		while (bids[i].title.compare(pivotValue.title) < 0);
		do
		{
			j--;
		}
		while (bids[j].title.compare(pivotValue.title) > 0);
		if (i >= j)
		{
			return j;
		}
		swap(bids[i], bids[j]);
	}
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids Address of the vector<Bid> instance to be sorted
 * @param begin The beginning index to sort on
 * @param end The ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end)
{
	if (begin < end)
	{
		int partitionIndex = partition(bids, begin, end);
		quickSort(bids, begin, partitionIndex);
		quickSort(bids, partitionIndex + 1, end);
	}
}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids)
{
	//define min as int (index of the current minimum bid)
	int min;

	// check size of bids vector
	// set size_t platform-neutral result equal to bid.size()
	size_t size = bids.size();

	// pos is the position within bids that divides sorted/unsorted
	// for size_t pos = 0 and less than size -1 
	for (size_t i = 0; i < size - 1; ++i)
	{
		// set min = pos
		min = i;

		// loop over remaining elements to the right of position
		for (size_t j = i + 1; j < size; ++j)
		{
			// if this element's title is less than minimum title
			if (bids[j].title.compare(bids[min].title) < 0)
			{
				// this element becomes the minimum
				min = j;
			}
		}
		// swap the current minimum with smaller one found
		if (min != i)
		{
			// swap is a built in vector method
			swap(bids[i], bids[min]);
		}
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch)
{
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[])
{
	// process command line arguments
	string csvPath;
	switch (argc)
	{
	case 2:
		csvPath = argv[1];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
	}

	// Define a vector to hold all the bids
	vector<Bid> bids;

	// Define a timer variable
	clock_t ticks;

	int choice = 0;
	while (choice != 9)
	{
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Selection Sort All Bids" << endl;
		cout << "  4. Quick Sort All Bids" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			// Initialize a timer variable before loading bids
			ticks = clock();

		// Complete the method call to load the bids
			bids = loadBids(csvPath);

			cout << bids.size() << " bids read" << endl;

		// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 2:
			// Loop and display the bids read
			for (int i = 0; i < bids.size(); ++i)
			{
				displayBid(bids[i]);
			}
			cout << endl;

			break;

		// FIXME (1b): Invoke the selection sort and report timing results
		case 3:
			ticks = clock();

			selectionSort(bids);

			ticks = clock() - ticks; // Calculate elapsed ticks

			cout << bids.size() << " bids sorted" << endl;
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		// FIXME (2b): Invoke the quick sort and report timing results
		case 4:
			// Initialize a timer variable before sorting bids
			ticks = clock();

		// Perform quick sort on all bids
			quickSort(bids, 0, bids.size() - 1);

			cout << bids.size() << " bids read" << endl;

		// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

		case 9:
			cout << "Good bye." << endl;
			return 0;

		default:
			cout << "Not a valid option. Please try again." << endl;

			break;
		}
	}

	// cout << "Good bye." << endl;

	return 0;
}
