//simple
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//for uint64 hash 
typedef unsigned long long ll;
auto random_address = [] { char* p = new char; delete p; return ll(p); };
const ll seed = chrono::high_resolution_clock::now().time_since_epoch().count() * (random_address() | 1);

mt19937_64 rng(seed);