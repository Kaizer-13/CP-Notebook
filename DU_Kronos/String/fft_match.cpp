using ld = double;
using cd = complex<ld>;
const ld PI = acos(-1.0);
const ld eps = 1e-6;

void fft(vector<cd>& a, bool invert)
{
    int n = (int)a.size();

    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1) {
        ld ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cosl(ang), sinl(ang));
        for(int i = 0; i < n; i += len) {
            cd w(1);
            for(int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if(invert) {
        for(cd& x : a) {
            x /= n;
        }
    }
}

vector<i64> multiply(vector<cd> const& a, vector<cd> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < (int)a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<i64> res(n);
    for(int i = 0; i < n; i++) {
        if(abs(fa[i].imag()) < eps) {
            res[i] = round(fa[i].real());
            if(abs(res[i] - fa[i].real()) > eps) {
                res[i] = -1;
            }
        } else {
            res[i] = -1;
        }
    }
    return res;
}

int main() 
{
    /*
        |t| <= |s|
        Want to check if t occurs as a substring of s
    */
    string s, t; cin >> s >> t;
    vector <cd> sa(s.size()), ta(t.size());
    for (int i = 0; i < s.size(); ++i) {
        ld ang = 2 * PI * (s[i] - 'a' + 1) / 27;
        sa[i] = cd(cosl(ang), sin(ang));
    }
    for (int i = 0; i < t.size(); ++i) {
        ld ang = 2 * PI * (t[i] - 'a' + 1) / 27;
        ta[t.size() - 1 - i] = cd(cosl(ang), -sin(ang));
    }
    vector<i64> mul = multiply(sa, ta);
    for (int i = 0; i < sa.size(); ++i) {
        if (mul[i] == ta.size()) {
            cout << i - ta.size() + 1 << ' ';
        }
    }
    cout << '\n';
}