# Permutations

## Premise
Given a set of items, return all possible permutations.

I found this problem within a [blog entry](https://dev.to/reggylong/how-i-went-from-failing-every-interview-to-a-job-at-amazon) at [dev.to](https://dev.to/) and couldn't stop thinking about it until I came up with a solution.

## Implementation
The input is assumed to be a series of characters; here, they are stored in Python lists. To build the permutations, we start with a function `perm_input()` that sets up some initial structures and initiates a recursive subroutine `perm_assemble()`.

Our major structures are as follows (where "list" refers to a Python list):

| Name | Type | Contents |
| --- | --- | --- |
| `assembled` | list | One partially-assembled permutation of items.
| `remaining` | list | The items that have not yet been added to the `assembled` list.
| `masterlist` | list of lists | A list of all completed permutations.

At each call to `perm_assemble()`, there are two possible courses of action. If the `remaining` list is empty, then we know that a permutation is complete, and we can add the permutation to the `masterlist` and exit the call. Otherwise, we make enough copies of `assembled` and `remaining` to match the number of available items in `remaining`. For each of these copies, we transfer a distinct item from `remaining` onto `assembled` and call `perm_assemble()` with these new copies.

## Further Discussion
### Input-checking
It should be noted that the input characters are not tested for distinctness. Thus, if we have something like `['a', 'a', 'a']` as the input, the output will be six copies of `['a', 'a', 'a']` even though there's really only one distinct permutation.  

### Efficiency
Given that the required output (all permutations) is exponential on the number of input items, it is not possible to write an algorithm with sub-exponential complexity. However, with the extensive copying taking place in this code, it seems likely that some efficiencies could be gained in the way that the memory is written and re-written, especially with regard to the `masterlist`.