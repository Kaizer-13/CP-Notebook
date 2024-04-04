//r[i][j]= inverse of p[i] modulo p[j]
//ans= x[0]+x[1]*p[0]+x[2]*(p[0]*p[1])+...+x[k-1]*(p[0]*p[1]*p[2]*...*p[k-2])
//ans %= ((p[0]*p[1]*p[2]*...*p[k-1])

for (int i = 0; i < k; ++i) {
    x[i] = a[i];
    for (int j = 0; j < i; ++j) {
        x[i] = r[j][i] * (x[i] - x[j]);

        x[i] = x[i] % p[i];
        if (x[i] < 0)
            x[i] += p[i];
    }
}

ll mul= p[0],res=x[0],tot=1;
F(i,0,k)tot *= p[i];
F(i,1,k){
	res+= x[i]*mul;
	res %= tot;
	mul *= p[i];
}
res %= mul;

return res;
