#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
/// we can replace int with other data types
/// If the data type is user defined, we need to define less operator for that type
typedef tree<
    int ,
    null_type ,
    less < int > , // "less_equal<int>," for multiset
    rb_tree_tag,
    tree_order_statistics_node_update > ordered_set;
/// ordered_set has become a data type, OS is an ordered_set
ordered_set OS;
