/***
    The code of the explanation can be found in "Gaussian Related Problem 1.cpp"

Problem :   Given n integers, pick a subset of the integers such
            that the xor sum of the subset is maximum.

Solution :

Clearly, if all the input numbers had a different length, the problem
would have a trivial solution: just iterate over the input numbers in
decreasing order by length, choosing each number if and only if XORing
it with the maximum so far increases the maximum, i.e. if and only if
its leading bit is not set in the current maximum.

"""
# Find maximum XOR of input, assuming that all input numbers have
# different length:
let max = 0
for each number n in input (sorted in descending order by length):
    if max < (max XOR n): let max = (max XOR n)
"""

The tricky part is when the input may contain multiple numbers with the same length,
since then it's not obvious which of them we should choose to include in the XOR.
What we'd like to do is reduce the input list into an equivalent form that doesn't
contain more than one number of the same length.

Conveniently, this is exactly what Gaussian elimination does:
it transforms a list of vectors into another list of vectors which have strictly
decreasing length, as defined above (that is, into a list which is in echelon form),
but which still spans the same linear subspace.

"""
# Preliminary phase: split numbers into buckets by length
for each number x in input:
    let k = length of x
    if k > 0: add x to bucket k

# Gaussian elimination:
for each bucket (in decreasing order by k):
    if this bucket is empty: skip rest of loop
    let x = arbitrary (e.g. first) number in this bucket
    remove x from this bucket
    add x to modified input list

    for each remaining number y in this bucket:
        remove y from this bucket
        let z = y XOR x
        let k = length of z
        if k > 0: add z to bucket k
"""

It's also possible to find the subset of input numbers giving the maximum XOR
using this algorithm: for each modified input number, you just need to somehow keep
track of which original input numbers it was XORed from. This is basically the same
algorithm as using Gaussian elimination to find a matrix inverse, just adapted to bit vectors.


***/
