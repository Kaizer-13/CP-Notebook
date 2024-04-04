int dis[MAX][MAX], P[MAX][MAX];
void warshall(int n) {
    int i,j,k;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(dis[i][j] != INF) P[i][j] = i;
            else P[i][j] = -1;
        }
    }
    for(k=0;k<n;k++) {
        for(i=0;i<n;i++) {
            for(j=0;j<n;j++){
                if(dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] <= dis[i][j]){
                    dis[i][j] = dis[i][k] + dis[k][j]; P[i][j] = k;
                }
            }
        }
    }
}

void printPath(int s,int d) {
    if(P[s][d] == -1) puts("No Path!");
    else if(P[s][d] == s) printf("%d\n",s);
    else{
        printPath(s,P[s][d]);
        printPath(P[s][d],d);
    }
}

/*** Print d when the function returns ***/
