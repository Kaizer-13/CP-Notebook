void compute(int L, int R, int optL, int optR){
  if(L > R) return;
  int M = L + R >> 1;
  pair<ll, int> best(1LL << 60, -1);
  for(int k = optL; k <= min(M, optR); k++){
    best = min(best, {dp[prv][k] + C[k + 1][M], k});
  }
  dp[now][M] = best.ff;
  compute(L, M - 1, optL, best.ss);
  compute(M + 1, R, best.ss, optR);
}
