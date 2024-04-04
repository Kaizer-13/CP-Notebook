vector<int> d1(n);  // maximum odd length palindrome centered at i
                    // here d1[i]=the palindrome has d1[i]-1 right characters from i
                    // e.g. for aba, d1[1]=2;
for (int i = 0, l = 0, r = -1; i < n; i++) {
  int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
  while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
    k++;
  }
  d1[i] = k--;
  if (i + k > r) {
    l = i - k;
    r = i + k;
  }
}
vector<int> d2(n);  // maximum even length palindrome centered at i
                    // here d2[i]=the palindrome has d2[i]-1 right characters from i
                    // e.g. for abba, d2[2]=2;
for (int i = 0, l = 0, r = -1; i < n; i++) {
  int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
  while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
    k++;
  }
  d2[i] = k--;
  if (i + k > r) {
    l = i - k - 1;
    r = i + k ;
  }
}
