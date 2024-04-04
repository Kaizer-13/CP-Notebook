/***
    If we need to find nCr % P where P is a prime but P can be
    less than n or r, we can use Lucas Theorem.

    nCm = ((n_0 C r_0) * (n_1 C r_1) * (n_2 C r_2) * ... * (n_k C r_k)) % P

    Where n_i is the i'th digit in P based representation of n
    and r_i is the i'th digit in P based representation of r

    ** What if P is a composite number? **

    P = (p_0 ^ a_0) * (p_1 ^ a_1) * ... * (p_k ^ a_k)
    where all p_i are prime numbers.

    nCr = (n!)/((r)!*(n-r)!)

    If all a_i are 1, then we can use lucas to find individual mods for
    each p_i and combine those using CRT

    If any a_i is greater than 1,

    Let's Suppose,  n! = (p_i ^ u) * x
                    (n-r)! = (p_i ^ v) * y
                    (r)! = (p_i ^ w) * z
                    (See the code for calculation of x,y,z when
                     n or r has large value)

    Let's suppose p_i ^ a_i = t,
    gcd(t,x) = gcd(t,y) = gcd(t,z) = 1, so, x,y,z will have modular inverse
    with respect to t (see Note 1)

    So, we will find ( x /(y*z) ) % (p_i^a_i) and then multiply the
    result by (p_i ^ s) where s = u - v - w;
    If, s is not smaller than a_i, then the result is 0.

    Then, we will use CRT to combine the result.
    Actually, we don't need Lucas theorem anymore. This technique
    will work for a_i = 1 also.


    *****************Note 1*******************
    phi(p^a) = (p^a) - (p^(a-1)) if p is prime

    a ^ phi(p^x) = 1 (mod p^x)  if gcd(a,p) = 1
    modular inverse of a with respect to p^a is
    a ^ ( phi(p^x) - 1 ) % (p^x)
    *******************************************
***/



/// returns factorail(n) % (p^a) ignoring prime number p
/// can be done using a loop if n is small
/// complexity p^a * log(p^a)

ll fact[MAX]; /// size at least p^a

ll call(ll n,ll p,ll a) {
    ll ret = 1LL;
    ll y,x,m = 1;

    ///m = p^a
    for(ll i=1;i<=a;i++) m *= p;

    fact[0] = 1;
    for(ll i=1;i<=m;i++){
        if(i%p==0) fact[i] = fact[i-1];
        else fact[i] = (fact[i-1]*i)%m;
    }

    while(true){
        if(n==0) break;

        y = n/m;
        ret *= bm(fact[m],y,m);
        ret %= m;

        y = n%m;

        ret *= fact[y];
        ret %= m;
        n /= p;
    }
    return ret;
}
