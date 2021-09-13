#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

void merge(char** arr, int f, int m, int l) {
	int size1 = m - f + 1;
	int size2 = l - m;

	char** sub1 = new char* [size1];
	for (int i = 0; i < size1; i++)
	{
		sub1[i] = new char[size1];
	}
	char** sub2 = new char* [size2];
	for (int j = 0; j < size2; j++)
	{
		sub2[j] = new char[size2];
	}

	for (int i = 0; i < size1; i++) {
		sub1[i] = arr[f + i];
	}
	for (int j = 0; j < size2; j++) {
		sub2[j] = arr[m + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = f;

	while (i < size1 && j < size2) {
		if (strcmp(sub1[i], sub2[j]) <= 0) {
			arr[k] = sub1[i];
			i++;
		}
		else {
			arr[k] = sub2[j];
			j++;
		}
		k++;

	}

	while (i < size1) {
		arr[k] = sub1[i];
		i++;
		k++;
	}

	while (j < size2) {
		arr[k] = sub2[j];
		j++;
		k++;
	}

}

void mergeSort(char** arr, int s, int e) {
	if (s < e) {

		int m = s + (e - s) / 2;

		mergeSort(arr, s, m);
		mergeSort(arr, m + 1, e);

		merge(arr, s, m, e);
	}
}

void encoder(string n, string sortMethod)
{

	if (sortMethod != "insertion" && sortMethod != "merge")
	{
		cout << "Error, chose unavailable sorting method\n" << endl;
		return;
	}

	// count string size
	int i = 0;
	while (n[i] != '\0')
	{
		i++;
	}
	
	// create original table
	char** original = new char* [i];
	for (int j = 0; j < i; j++)
	{
		original[j] = new char[i];
	}

	// fill original table with shifting
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			original[((k+j)%i)][j] = n[k];
		}
	}

	// create sorted table
	char** sorted = new char* [i];
	for (int j = 0; j < i; j++)
	{
		sorted[j] = new char[i];
	}

	// reverse sorted table
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			sorted[i-k-1][j] = original[k][j];
		}
	}

	// lexicographic order
	if (sortMethod == "insertion")
	{
		// insertion sort
		int j, k;
		char* key = new char[i];
		for (int j = 1; j < i; j++) 
		{
			key = sorted[j];
			k = j - 1;
			while (k >= 0 && strcmp(sorted[k], key) > 0) 
			{
				sorted[k + 1] = sorted[k];
				k--;
			}
			sorted[k + 1] = key;
		}
	}
	else
	{
		//call merge sort
		mergeSort(sorted, 0, i - 1);
	}

	// reverse sorted table
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			original[j][i - k - 1] = sorted[j][k];
		}
	}

	// copy from temp(original) to sorted array
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			sorted[j][k] = original[j][k];
		}
	}

	// find index of original string
	// take first letter from each string from sorted table
	string first = "";
	for (int j = 0; j < i; j++)
	{
		bool check = true;
		for (int k = 0; k < i; k++)
		{
			if (sorted[j][k] != n[k])
			{
				check = false;
			}
		}
		
		if (check)
		{
			cout << j << endl;
		}
		
		first += sorted[j][0];
	}

	//output clusters
	for (int j = 0; j < i; j++)
	{
		int count = 0;
		int k = j;
		while (k < i && first[j] == first[k])
		{
			count++;
			k++;
		}
		j = j + count - 1;
		cout << count << " ";
		cout << first[j] << " ";
	}

	cout << endl;
}

int main(int argc, char** argv)
{
	string n;
	getline(cin, n);
	string temp;
	while (n != "\n")
	{
		temp = n;
		encoder(n, argv[1]);
		getline(cin, n);
		if (temp == n)
			break;
	}
}