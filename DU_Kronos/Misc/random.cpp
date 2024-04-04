// shuffle(v.begin(), v.end(), default_random_engine(rnd(1, 1000)));

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r) (rng);
}
