ll mod=(1e9)+7;
 
struct Matrix{
    int row, col;
    vector<vector<ll>> mat;
    
    Matrix(int x, int y){
        row=x;
        col=y;
        mat.assign(row,vector<ll>(col,0));
    }

    Matrix operator *(Matrix &other){
        assert(col==other.row);
        Matrix product(row,other.col);
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                for(int k=0;k<other.col;k++){
                    product.mat[i][k]=(product.mat[i][k]+(mat[i][j]*other.mat[j][k])%mod)%mod;
                }
            }
        }
        return product;
    }
};


Matrix expo(Matrix &m, ll n){
    assert(m.row==m.col);
    Matrix ret(m.row,m.col);
    for(int i=0;i<m.row;i++) ret.mat[i][i]=1;
    while(n){
        if(n&1) ret=ret*m;
        n/=2;
        m=m*m;
    }
    return ret;
}
