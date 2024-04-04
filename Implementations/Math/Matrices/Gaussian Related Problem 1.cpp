/***
    http://codeforces.com/blog/entry/9518
    Problem : Given n numbers, you have to take a subset.
              Let X denote the xor of the numbers of the subset.

              You will be given some conditions on the bits of X.
              condition(b,1) means try to make the b'th bit of X 1
              condition(b,0) means try to make the b'th bit of X 0
              The conditions will be ordered

              Suppose 6 conditions are given.
              Y = 100110 denotes condition 1,4,5 are satisfied
              We will try to maximize Y
***/

const int MAX = 100010;

ll ara[MAX];
bitset <MAX> mat[70];
int n; /// Number of input integers/number of columns in matrix
int row, ans[MAX], where[MAX];

void addCondition(int bn,int val){
    ++row;

    mat[row].reset();
    mat[row][n] = val;

    for(int col=0; col<n; col++) mat[row][col]=( (ara[col]>>bn) & 1 );

    for(int col=0; col<n; col++){
        if(mat[row][col]){
            if(where[col]) mat[row] ^= mat[where[col]];
            else break;
        }
    }
    for(int col=0; col<n; col++){
        if(mat[row][col]){
            where[col]=row;
            return;
        }
    }
    --row;
}

struct data {
    int bitNumber;
    int val; /// preferred value for that bit
};
vector <data> conditions;



/// m denotes maximum number of bits of any number in the input
void solve() {
    CLR(where);
    row = 0;
    for(int i=0;i<conditions.size();i++){
        addCondition(conditions[i].bitNumber,conditions[i].val);
    }
    for(int i=n-1;i>=0;i--){
        if(mat[where[i]][n]){
            ans[i] = 1;
            for(int j=1;j<=row;j++){
                if(mat[j][i]) mat[j].flip(n);
            }
        }
        else ans[i] = 0;
    }
}

int main() {
    /// scan n integer numbers(0 based)
    /// fill conditions vector

    solve();

    /// now ans[i] will be 1 if the i'th integer is taken in the subset
    return 0;
}
