#include <bits/stdc++.h>
using namespace std; 

#define A 31
#define B 1000000007 

long long inv(long long a, long long b){
    return 1<a ? b - inv(b%a,a)*b/a : 1;
}

template<typename T>
struct ModPlus : std::binary_function<T, T, T>
{
private: 
    long long m; 
    
public: 
    ModPlus(long long m) : m(m) {}

    T operator()(T a, T b) const
    {
        return (a + b) % m; 
    }
};

template<typename T>
struct ModNegate : std::unary_function<T, T>
{
private: 
    long long m;

public: 
    ModNegate(long long m) : m(m) {}

    T operator()(T a) const
    {
        return m - (a % m); 
    }
};
 
namespace ttl
{
    template <typename T, typename Op = std::plus<T>, typename Inv = std::negate<T>>
    class FenwickTree
    {
    private: 
        std::vector<T> tree; 
        Op op; 
        Inv inv; 

    public: 
        FenwickTree(int n, Op op = Op(), Inv inv = Inv()) : 
            tree(n + 1, T()), op(op), inv(inv) {} 

        /**
         * @brief Updates the Fenwick tree at index with the given value.
         */
        void update(int index, T value)
        {
            while (index < tree.size()) 
            {
                tree[index] = op(tree[index], value); 
                index += index & -index; 
            }
        } 

        /**
         * @brief Updates the Fenwick tree in the range [left, right] with the given value.
         */
        void range_update(int left, int right, T value)
        {
            update(left, value); 
            update(right + 1, inv(value)); 
        }

        /**
         * @brief Queries the Fenwick tree for the cumulative value up to the given index.
         */
        T query(int index)
        {
            T result = T(); 
            while (index > 0) 
            {
                result = op(result, tree[index]); 
                index -= index & -index; 
            }
            return result; 
        } 
        
        /**
         * @brief Queries the Fenwick tree for the cumulative value in the range [left, right].
         */
        T range_query(int left, int right)
        {
            return op(query(right), inv(query(left - 1))); 
        }
    }; 
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);  
    int n, m; cin >> n >> m;
    string s; cin >> s; 
    const long long inv_a = inv(A, B); 
    vector<long long> pw(n, 1), inv_pw(n, 1); 
    for(int i = 1; i < n; i++) {
        pw[i] = (pw[i - 1] * A) % B; 
        inv_pw[i] = (inv_pw[i - 1] * inv_a) % B;
    }
    struct ModPlus<long long> mod_plus(B); 
    struct ModNegate<long long> mod_negate(B); 
    ttl::FenwickTree<long long, ModPlus<long long>, ModNegate<long long>> 
        left(n, mod_plus, mod_negate), right(n, mod_plus, mod_negate);
    for(int i = 1; i <= n; i++) {
        left.update(i, ((s[i - 1] - 'a' + 1) * pw[n - i]) % B); 
        right.update(i, ((s[i - 1] - 'a' + 1) * pw[i - 1]) % B); 
    }
    while(m--) {
        int t; cin >> t; 
        if(t == 1) {
            int k; cin >> k; 
            char x; cin >> x; 
            left.update(k, mod_negate(((s[k - 1] - 'a' + 1) * pw[n - k]) % B));
            left.update(k, ((x - 'a' + 1) * pw[n - k]) % B);
            right.update(k, mod_negate(((s[k - 1] - 'a' + 1) * pw[k - 1]) % B));
            right.update(k, ((x - 'a' + 1) * pw[k - 1]) % B);
            s[k - 1] = x; 
        } else {
            int l, r; cin >> l >> r; 
            long long lhash = (left.range_query(l, r) * inv_pw[n - r]) % B; 
            long long rhash = (right.range_query(l, r) * inv_pw[l - 1]) % B;
            cout << (lhash == rhash ? "YES" : "NO") << '\n';
        }
    }
}
