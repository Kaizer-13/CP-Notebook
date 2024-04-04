/***
Problem : https://codeforces.com/contest/1101/problem/G

You are given an array a[0...(n-1)] of integer numbers.
Your task is to divide the array into the maximum number of
non empty segments in such a way that :
there doesn't exist a non-empty subset of segments such that the XOR-sum
of the numbers from them is equal to 0.

Solution :

Build a cumilitive xor array. ( cum[i] = cum[i-1] ^ a[i] )
Build a matrix where row[i] = binary representation of cum[i]
Answer is the rank of the matrix.

If cum[n-1] = 0, no solution.
***/


/***
Problem :
Given a set S of size N, find the number of distinct integers that
can be represented using xor over the set of the given elements.

Solution :
This is 2^x, where x is the size of the basis of the given set of size N.
***/

