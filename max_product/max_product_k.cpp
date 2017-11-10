/*
 * max_product_k.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: degagnon
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct locVal {
	int loc;
	int val;
};

bool inverseSort (int i, int j) { return i>j; }

int max_product_finder_k(int intlist[], int listlen, int k);
locVal min_abs_loc(int array[], int k);

int main(int argc, char** argv)
{
	int a[] = {4, 2, -6, 1, -5, 3};
	int ans = max_product_finder_k(a, 6, 3);
	cout << ans;
	return 0;
}

int max_product_finder_k(int intlist[], int listlen, int k)
{
	int max_p[k]; fill(max_p, max_p + k, 0);
	locVal max_p_min = min_abs_loc(max_p, k);
	int max_n[k-k%2]; fill(max_n, max_n + k-k%2, 0);
	locVal max_n_min = min_abs_loc(max_n, k-k%2);

	for (int i = 0; i < listlen; ++i)
	{
		cout << intlist[i] << '\n';
		if (intlist[i] > max_p_min.val)
		{
			max_p[max_p_min.loc] = intlist[i];
			max_p_min = min_abs_loc(max_p, k);
//			cout << intlist[i] << " added to positive array.\n" <<
//					"New min at position " << max_p_min.loc <<
//					" with value " << max_p_min.val << '\n';
		}
		else if (intlist[i] < max_n_min.val)
		{
			max_n[max_n_min.loc] = intlist[i];
			max_n_min = min_abs_loc(max_n, k-k%2);
		}
	}

	sort(max_p, max_p+k, inverseSort);
	sort(max_n, max_n+k-k%2);

	for (int i = 0; i < k; ++i)
	{
		cout << "Positive array item " << i << " is " << max_p[i] << '\n';
	}
	for (int i = 0; i < k-k%2; ++i)
	{
		cout << "Negative array item " << i << " is " << max_n[i] << '\n';
	}

	int count_p = 0;
	int count_n = 0;
	int prod_pos = 0;
	int prod_neg = 0;
	int max_prod = 1;

	if (k%2 == 1)
	{
		max_prod = max_p[count_p];
		count_p++;
	}

	while (count_p + count_n < k)
	{
		prod_pos = max_p[count_p] * max_p[count_p+1];
		prod_neg = max_n[count_n] * max_n[count_n+1];
		if (prod_pos >= prod_neg)
		{
			max_prod *= prod_pos;
			count_p += 2;
		}
		else
		{
			max_prod *= prod_neg;
			count_n += 2;
		}
	}

	return max_prod;
}

locVal min_abs_loc(int array[], int k)
{
	locVal result;
	result.loc = 0;
	result.val = array[result.loc];
	for (int i = 0; i < k; ++i)
	{
//		cout << "Evaluating position " << i << " with value " << array[i] << '\n';
		if (array[i] < abs(result.val))
		{
			result.loc = i;
			result.val = array[result.loc];
//			cout << "New minimum should be at position " << i << " with value " << array[i] << '\n';
//			cout << "New minimum identified at position " << result.loc << " with value " << result.val << '\n';
		}
	}
	return result;
}
