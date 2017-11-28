# Maximum Product of k Integers

## Premise
This [Code Challenge](https://discuss.codecademy.com/t/challenge-max-product-finder/113074) was posted by [Codecademy](https://www.codecademy.com/), asking participants to find the largest product of `k` integers from an arbitrary list of positive and negative integers. Three levels of difficulty are provided:

| Difficulty | Case |
| --- | --- |
| Basic | Assume `k = 3` |
| Intermediate | Write code for arbitrary `k` |
| Hard | Write the above as efficiently as possible |

More details can be found on the [challenge webpage](https://discuss.codecademy.com/t/challenge-max-product-finder/113074).

## Implementation
I wrote solutions in both Python and C++; these solutions do not depend on one another, but they do take a similar approach.

This discussion will focus on the general `max_product_finder_k()`, since the basic case of `max_product_finder()` can be regarded as the same problem but with known constant `k = 3`.

Since we want to make the code as efficient as possible, we want to avoid too many iterations through the integer list, and we especially want to avoid the brute-force approach of "calculate every combination", which would have exponential complexity. By maintaining two smaller lists, we can get by with just one iteration through the integer list. The positive list is of size `k`, keeping track of the largest positive integers seen so far, and the negative list is of size `k` or `k-1` (whichever is even), keeping track of the "largest" negative integers seen so far (that is, the most-negative values).

For odd `k`, the largest positive integer will be included in the final product, and all other components can be multiplied in positive pairs or negative pairs. For even `k`, all components come in positive pairs or negative pairs. To make sure that we obtain the largest product, we sort the positive and negative lists and step through pairs in both lists at the same time, choosing the pair with the larger product.

## Further Discussion
### Input Limitations
It should be noted that the above implementation assumes that there will be a blend of both positive and negative numbers. If all numbers are positive, then the process still works, since the end result is simply the product of the largest k numbers. If k is even, then the process still works, since pairs of negative numbers multiply to a positive result. But what happens if all numbers are negative and `k` is odd? There is a problem where the products are calculated, specifically here:
```python
    ptr_pos = 0
    ptr_neg = 0
    max_prod = 1
    if k % 2 == 1:
        # For odd k, the largest positive integer must be included.
        max_prod *= max_list_pos[ptr_pos]
        ptr_pos += 1
```
If `k` is odd and `max_list_pos` is empty, then this code tries to multiply by a nonexistent number. Better unit testing could have revealed this problem sooner.

If I were to rewrite the code, I might try to maintain a third list that holds the least-negative `k` values (that is, negative numbers with the smallest absolute values). Once at least one positive integer is found, this list can be ignored, but if all numbers are negative and `k` is odd, then we would want to use the least-negative numbers in our product, not the most-negative numbers.

Supposing that we are permitted to use *up to* `k` integers (as opposed to *exactly* `k` integers), then we could use the process already in place and just modify the `if`-statements to avoid the problem of accessing an empty list.

### C++ Style
Looking at this code in November 2017, I find it to be a little more complicated than necessary. A few potential improvements:

* Elegant containers like `vector<int>` instead of C-style arrays requiring an additional length-variable.
* Different implementation of the `locVal` struct, either as separate variables, as a `pair` type, or perhaps as a full-fledged class with more object orientation. An OO approach could encapsulate the vector of `k` integers with helpful index information.
* Passing of variables by reference instead of passing by value. The impact is likely to be small at the moment but could become more significant with the above changes.
