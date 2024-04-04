(P1) We are given a text T and a pattern P. We have to compute all the occurrences of the pattern in the text.
(S1) |T| = n, |P| = m
     a[i] = cos(x(i)) + i sin(x(i)), x(i) = (2 * pi * T[i])/(26)
     b[i] = cos(y(i)) - i sin(y(i)), y(i) = (2 * pi * P[m - i - 1])/(26)
     C(x) = A(x) * B(x)
     If, c[m - 1 + i] = m, then P occurs in T at position i.

(P2) Given a pattern P and a Text T, |T| = n, |P| = m.
     Find the minimum hamming distance between any length m substring of text T with pattern P.
(S2) vector <int> tot(n + m - 1, 0);
     for(char ch = 'a'; ch <= 'z'; ch++) {
         vector <int> a, b, c;
         for(char x : T) a.push_back(x == ch);
         for(char x : P) b.push_back(x == ch);
         reverse(b.begin(), b.end());
         c = multiply(a, b);
         for(int i=0;i<c.size();i++) tot[i] += c[i];
     }
     (m - tot[m - 1 + i]) = hamming distance between P and T[i : m+i)
