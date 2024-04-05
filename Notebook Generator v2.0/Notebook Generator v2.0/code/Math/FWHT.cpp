const int N = 1 << 20;
// apply modulo if necessary
void fwht_xor(int *a, int n, int dir = 0) {
    for (int h = 1; h < n; h <<= 1) {
        for (int i = 0; i < n; i += h << 1) {
            for (int j = i; j < i + h; ++j) {
                int x = a[j], y = a[j + h];
                a[j] = x + y, a[j + h] = x - y;
                if (dir) a[j] >>= 1, a[j + h] >>= 1;
            }
        }
    }
}
void fwht_or(int *a, int n, int dir = 0) {
    for (int h = 1; h < n; h <<= 1) {
        for (int i = 0; i < n; i += h << 1) {
            for (int j = i; j < i + h; ++j) {
                int x = a[j], y = a[j + h];
                a[j] = x, a[j + h] = dir ? y - x : x + y;
            }
        }
    }
}
void fwht_and(int *a, int n, int dir = 0) {
    for (int h = 1; h < n; h <<= 1) {
        for (int i = 0; i < n; i += h << 1) {
            for (int j = i; j < i + h; ++j) {
                int x = a[j], y = a[j + h];
                a[j] = dir ? x - y : x + y, a[j + h] = y;
            }
        }
    }
}