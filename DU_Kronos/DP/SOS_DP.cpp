/***
    S(mask,i) denotes those submasks of mask which differ
    from mask only in the least significant i+1 bits ( 0, 1, 2, ...., i --> 0 based indexing)
    Example : S(1011010,3) = {1011010,1010010,1011000,1010000}


    if(bit i is on)
        S(mask, i) = S(mask, i - 1) U S(mask ^ (1<<i), i - 1)
    else
        S(mask, i) = S(mask, i - 1)


    Let Sum(mask,i) denote the sum of the all A[x] where x element of S(mask,i)
    So, Sum(mask,N-1) will contain SOS DP result for a particular mask

    Recurrence :
    if(i'th bit is on)
        Sum(mask, i) = Sum(mask, i-1) + Sum(mask ^ (1<<i), i-1)
    else
        Sum(mask, i) = Sum(mask, i-1)
***/

///iterative version
    for(int mask = 0; mask < (1<<N); ++mask){
        dp[mask][-1] = A[mask];	///handle base case separately (leaf states)
        for(int i = 0;i < N; ++i){
            if(mask & (1<<i)) dp[mask][i] = dp[mask][i-1] + dp[mask ^ (1<<i)][i-1];
            else dp[mask][i] = dp[mask][i-1];
        }
        F[mask] = dp[mask][N-1];
    }
///memory optimized version
    for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
    for(int i = 0;i < N; ++i)
        for(int mask = 0; mask < (1<<N); ++mask){
            if(mask & (1<<i))
                F[mask] += F[mask^(1<<i)];
        }
/// O( N * 2^N )