/***
    Complexity --> O( min(n,m) * nm )
    *** Keep the elements of matrix between 0 to P-1
    *** In every test case, clear mat first and then do the changes
***/

const int SZ = 105;
const int MOD = 1e9 + 7;

int mat[SZ][SZ]; /// Augmented Matrix
int where[SZ]; /// where[i] denotes the row index of the pivot element of column i
int ans[SZ];

ll bigMod(ll a,ll b,ll m){
    ll ret = 1LL;
    a %= m;
    while (b){
        if (b & 1LL) ret = (ret * a) % m;
        a = (a * a) % m;
        b >>= 1LL;
    }
    return ret;
}

/// n for row, m for column, modulo P
int Gauss(int n,int m,int P) {
    SET(where); /// sets to -1
    for(int row=0,col=0;col<m && row<n;col++){
        int max_row = row;
        for(int i=row;i<n;i++)
            if( mat[i][col] > mat[max_row][col] ) max_row = i;

        if( mat[max_row][col] == 0 ) continue;

        for(int i=col;i<=m;i++) swap(mat[row][i],mat[max_row][i]);

        where[col] = row;

        int mul,minv = bigMod(mat[row][col],P-2,P);
        int temp;
        for(int i=row+1;i<n;i++){
            if( mat[i][col] != 0){
                mul = ( mat[i][col] * (long long) minv ) % P;
                for(int j=col;j<=m;j++) {
                    temp = mat[i][j];
                    temp -= ( ( mul * (long long) mat[row][j] ) % P );
                    temp += P;
                    if( temp >= P ) temp -= P;
                    mat[i][j] = temp;
                }
            }
        }
        row++;
    }

    /// checking 0 row
    bool zero;
    for(int i=0;i<n;i++){
        zero = true;
        for(int j=0;j<m;j++) {
            if(mat[i][j]) {
                zero = false; break;
            }
        }
        if( zero and mat[i][m] ) return 0; ///no solution
    }

    /// back substitution
    int sltn;
    int cur;
    for(int j=m-1;j>=0;j--){
        if( where[j] == -1 ) {
            ans[j] = 0; /// Infinitely many solutions, determining one
            continue;
        }
        sltn = mat[where[j]][m];
        cur = where[j];
        for(int i = j+1; i<m; i++) {
            sltn -= ( ( mat[cur][i] * (long long) ans[i] ) % P );
            sltn += P;
            if(sltn >= P) sltn -= P;
        }
        ans[j] = ( sltn * (long long) bigMod(mat[cur][j],P-2,P) ) % P;
    }

    int cnt = 0;
    for(int j=0; j<m; j++)
        if(where[j]==-1) cnt++;

    return bigMod(P,cnt,MOD);
}
