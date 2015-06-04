// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2014

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#define BUCKET1 1000
#define BUCKET2 100000
#define COUNT 1000000

//Global variable declaration
int countMap [COUNT];
int decimalIndex1, decimalIndex2;
int decimalLocation;
int substringIndex;
int bucketIndex;
int tmp;
int firstDigit;
float tempFloat;

Data * countData [COUNT];

list<Data *> newList;
list<Data *> bucket1 [BUCKET1];
list<Data *> bucket2 [10][BUCKET2];

list<Data *>::iterator it, tmpIt, holePos;

//. location search for T1, T2, T4
int locateDecimal(const Data *d) {
	int i=20;
	while(d->data.at(i)!= '.') {
		i--;
	}
	return i;
}

//Generic Compare Function for numbers with different digits
bool compare(const Data* a, const Data* b) {
	decimalIndex1=locateDecimal(a);
	decimalIndex2=locateDecimal(b);
	if (decimalIndex1 == decimalIndex2){
		return (a->data) < (b->data);
	}else{
		return decimalIndex1 < decimalIndex2;
	}
}

//String Comparator. This function compares numbers with same decimal points without wasting time
bool compareStrings(const Data* a, const Data* b) {
	return a->data < b->data;
}

//Comparator for T3
bool compare3(const Data* a, const Data* b) {
	decimalIndex1 = (a->data).find(".");
	decimalIndex2 = (b->data).find(".");
	if (decimalIndex1 == decimalIndex2){
		return (a->data) < (b->data);
	}else{
		return decimalIndex1 < decimalIndex2;
	}
}

//Sample = T1, bucket sort
void bucketSort(list<Data *> &l) {
	//populate buckets
	for (it=l.begin(); it!=l.end(); it++){
		//-17 because digits there are 1000 buckets
		substringIndex = locateDecimal(*it) - 17;
		if (substringIndex<=0){
			bucket1[0].push_back(*it);
		}else{
			bucketIndex = atoi((*it)->data.substr(0,substringIndex).c_str());
			bucket1[bucketIndex].push_back(*it);
		}
	}

	bucket1[0].sort(compare);
	newList.splice(newList.end(),bucket1[0]);

	for (int i=1; i<=BUCKET1; i++) {
		bucket1[i].sort(compareStrings);
		newList.splice(newList.end(),bucket1[i]);
	}

	l.swap(newList);
}

//Sample = T2, bucket sort
void bucketSort2(list<Data *> &l) {
	//populate buckets
	for (it=l.begin(); it!=l.end(); it++){
		decimalLocation = locateDecimal(*it);
		//-15 because there are 100000 buckets
		substringIndex = decimalLocation - 15;
		bucketIndex = atoi((*it)->data.substr(0,5).c_str());
		
		if (decimalLocation<20){
			newList.push_back(*it);
		}else{
			firstDigit = (*it)->data.at(0)-48;
			bucket2[firstDigit][bucketIndex].push_back(*it);
		}
	}

	newList.sort(compare);
	newList.splice(newList.end(),bucket2[1][0]);

	for(int i = 1; i < 10; i++){
		for(int j = 0; j < BUCKET2; j++){
			bucket2[i][j].sort(compareStrings);
			newList.splice(newList.end(),bucket2[i][j]);
		}
	}

	l.swap(newList);
}

//Sample = T2, counting sort
void countingSort3(list<Data *> &l) {
	for (it=l.begin(); it!=l.end(); ++it) {
		// index into array of bucket1 and formatted #s by converting to int (tmp)
		tempFloat = (1000*atof(((*it)->data).c_str()));
		tmp = tempFloat;
		countData[tmp]=*it;
		countMap[tmp]++;
	}
	// push Data ptrs in order into new linked list
	for (int i=0; i<COUNT; i++) {
		while(countMap[i]--){
			newList.push_back(countData[i]);
		}
	}
	// replace list l with new list newList
	l.swap(newList);
}

void insertionSort4(list<Data *> &l) {
	// start at 2nd position for insertion sort
	it = l.begin();
	it++;
	for (; it!=l.end(); ++it){
		holePos = it;
		tmpIt = holePos; 
		tmpIt--;
		while (holePos!=l.begin() && (*holePos)->data < (*tmpIt)->data) {
			iter_swap(holePos,tmpIt);
			holePos--;
			tmpIt--;
		}
	}
}

void sortDataList(list<Data *> &l) {
	//Decide which sort to use
	int lengthList = l.size();
	int lengthNum = ((*l.begin())->data).length();
	it = l.begin();

	if(lengthNum < 8){
		countingSort3(l);	// Sample = T3
	}else if(lengthList < 101001){
		bucketSort(l); 		//Sample = T1
	}else{
		string first, second;
		first = (*it) -> data;
		it++;
		second = (*it) -> data;

		if (first.substr(0,10) == second.substr(0,10)){
			insertionSort4(l); // Sample = T4
		}else{
			bucketSort2(l); // Sample = T2
		}
	}
}
