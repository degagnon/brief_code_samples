# coding=utf-8
"""Code Challenge #10: June 14, 2017
Every week, we feature the type of brain-teasing question that might be asked in a full-stack developer's job interview at places such as Google and Facebook.

This week's challenge was reported to have been asked in interviews at Google:

Basic Difficulty

Given an array of integers, write a function, maxProductFinder, that finds the largest product that can be obtained from any 3 integers in the array.
Function Name: maxProductFinder
Input: int[] - an array of integers
Output: an integer – the maximum product found from any three integers in the array
Example: maxProductFinder([-8, 6, -7, 3, 2, 1, -9]) => 432
You may assume that the array contains at least three integers
Please run the following array as a test: [-6, -8, 4, 2, 5, 3, -1, 9, 10]
Find out more about basic challenges.

Intermediate difficulty

Given an array of integers, write a function, maxProductFinderK, that can be obtained from any k integers in the array.
Function Name: maxProductFinderK
Input: int[] - an array of integers and an integer k where k is the number of ints that can be used
Output: an integer – the maximum product found from any k integers in the array
Example: maxProductFinderK([-8, 6, -7, 3, 2, 1, -9], 2) => 72
You may presume that the length of the array of integers is greater or equal to k
Find out more about intermediate challenges.

Hard Difficulty

Write maxProductFinder and maxProductFinderK as efficiently as possible."""

import unittest

class TestProductFinder(unittest.TestCase):
    def test_demo_1(self):
        src = [-8, 6, -7, 3, 2, 1, -9]
        self.assertEqual(max_product_finder(src), 432)

    def test_demo_2(self):
        src = [-6, -8, 4, 2, 5, 3, -1, 9, 10]
        self.assertEqual(max_product_finder(src), 480)

    def test_demo_3(self):
        src = [-8, 6, -7, 3, 2, 1, -9]
        ktest = 2
        self.assertEqual(max_product_finder_k(src, ktest), 72)

def find_abs_min(array):
    if len(array) == 0:
        return (None, None)
    min_loc = 0
    min_val = array[min_loc]
    for loc, item in enumerate(array[1:]):
        if abs(item) < abs(min_val):
            min_val = item
            min_loc = loc + 1
    return (min_loc, min_val)

def max_product_finder(intlist):
    max_list_pos = []
    max_list_pos_min = None
    max_list_pos_min_loc = None
    max_list_neg = []
    max_list_neg_min = None
    max_list_neg_min_loc = None
    for _, number in enumerate(intlist):
        if number > 0:
            if len(max_list_pos) < 3:
                max_list_pos.append(number)
                max_list_pos_min = number
                if len(max_list_pos) == 3:
                    max_list_pos_min_loc, max_list_pos_min = find_abs_min(max_list_pos)
            else:
                if number > max_list_pos_min:
                    max_list_pos[max_list_pos_min_loc] = number
                    max_list_pos_min_loc, max_list_pos_min = find_abs_min(max_list_pos)
        if number < 0:
            if len(max_list_neg) < 2:
                max_list_neg.append(number)
                max_list_neg_min = number
                if len(max_list_neg) == 2:
                    max_list_neg_min_loc, max_list_neg_min = find_abs_min(max_list_neg)
            else:
                if abs(number) > abs(max_list_neg_min):
                    max_list_neg[max_list_neg_min_loc] = number
                    max_list_neg_min_loc, max_list_neg_min = find_abs_min(max_list_neg)

    max_list_pos.sort(reverse=True)
    max_list_neg.sort()
    print('Max list positive is {}'.format(max_list_pos))
    print('Max list negative is {}'.format(max_list_neg))

    prod_a = max_list_pos[0] * max_list_pos[1] * max_list_pos[2]
    prod_b = max_list_pos[0] * max_list_neg[0] * max_list_neg[1]
    max_prod = max(prod_a, prod_b)

    return max_prod

def max_product_finder_k(intlist, k):
    max_list_pos = []
    max_list_pos_min = None
    max_list_pos_min_loc = None
    max_list_neg = []
    max_list_neg_min = None
    max_list_neg_min_loc = None
    for _, number in enumerate(intlist):
        if number > 0:
            if len(max_list_pos) < k:
                max_list_pos.append(number)
                max_list_pos_min = number
                if len(max_list_pos) == k:
                    max_list_pos_min_loc, max_list_pos_min = find_abs_min(max_list_pos)
            else:
                if number > max_list_pos_min:
                    max_list_pos[max_list_pos_min_loc] = number
                    max_list_pos_min_loc, max_list_pos_min = find_abs_min(max_list_pos)
        if number < 0:
            if len(max_list_neg) < k - k % 2:
                # k - k % 2 is the largest even number less than or equal to k.
                max_list_neg.append(number)
                max_list_neg_min = number
                if len(max_list_neg) == k - k % 2:
                    max_list_neg_min_loc, max_list_neg_min = find_abs_min(max_list_neg)
            else:
                if abs(number) > abs(max_list_neg_min):
                    max_list_neg[max_list_neg_min_loc] = number
                    max_list_neg_min_loc, max_list_neg_min = find_abs_min(max_list_neg)

    max_list_pos.sort(reverse=True)
    max_list_neg.sort()
    print('Max list positive is {}'.format(max_list_pos))
    print('Max list negative is {}'.format(max_list_neg))

    ptr_pos = 0
    ptr_neg = 0
    max_prod = 1
    if k % 2 == 1:
        # For odd k, the largest positive integer must be included.
        max_prod *= max_list_pos[ptr_pos]
        ptr_pos += 1

    while ptr_pos + ptr_neg < k:
        prod_pos = max_list_pos[ptr_pos] * max_list_pos[ptr_pos + 1]
        prod_neg = max_list_neg[ptr_neg] * max_list_neg[ptr_neg + 1]
        print('Positive product is {} while negative product is {}'.format(prod_pos, prod_neg))
        if prod_pos >= prod_neg:
            max_prod *= prod_pos
            ptr_pos += 2
        else:
            max_prod *= prod_neg
            ptr_neg += 2

    return max_prod

if __name__ == '__main__':
    print(find_abs_min([9, 6, -8, 7]))
    suite = unittest.TestLoader().loadTestsFromTestCase(TestProductFinder)
    unittest.TextTestRunner(verbosity=2).run(suite)


