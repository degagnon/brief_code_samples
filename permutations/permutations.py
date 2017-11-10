# permutations.py
# given a list of items, return all possible permutations
# problem from https://dev.to/reggylong/how-i-went-from-failing-every-interview-to-a-job-at-amazon

import copy

def perm_input(input):
    print('Finding permutations of {}'.format(input))
    masterlist = []
    if len(input) > 0:
        perm_assemble([], input, masterlist)
    return masterlist

def perm_assemble(assembled, remaining, masterlist):
    if len(remaining) < 1:
        masterlist.append(assembled)
        return masterlist
    for index in xrange(len(remaining)):
        # we need to produce a different appended value and remaining list for each recursion
        assembled_new = copy.copy(assembled)
        remaining_new = copy.copy(remaining)
        assembled_new.append(remaining_new.pop(index))
        perm_assemble(assembled_new, remaining_new, masterlist)
    return

testinputs = [[],
              ['a'],
              ['1', '2'],
              ['a', 'b', 'c'],
              ['1', '2', '3', '4'],
              ['a', 'b', 'c', 'd', 'e']]
for step, test in enumerate(testinputs):
    result = perm_input(test)
    perm_list = [''.join(x) for x in result]
    print('Test {}: Input {} gives {} permutation(s): \n{}\n'.format(step, test, len(result), '\n'.join(perm_list)))