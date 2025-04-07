#include <bits/stdc++.h>
using namespace std; 
 
namespace ttl
{
    class SuffixArray {
    private: 
        std::vector<int> _p; // the suffix array
        std::vector<std::vector<int>> _c; // the equivalence classes
        std::vector<int> _lcp; // the longest common prefix array
    
    public: 
        SuffixArray(const std::string& s) : _p(s.size(), 0), _lcp(s.size(), 0) {
            // Construct alphabet and positions of characters
            std::set<char> alphabet(s.begin(), s.end()); 
            std::map<char, int> pos; 
            for(char ch : alphabet) pos[ch] = pos.size(); 
            
            // Initialize suffix array and equivalence classes for h=0 using counting sort
            std::vector<int> cnt (std::max(alphabet.size(), s.size()), 0);
            for(int i = 0; i < s.size(); i++) cnt[pos[s[i]]]++; 
            for(int i = 1; i < alphabet.size(); i++) cnt[i] += cnt[i - 1]; 
            for(int i = s.size()-1; i >= 0; i--) _p[--cnt[pos[s[i]]]] = i;
            _c.emplace_back(s.size(), 0); 
            _c.back()[_p[0]] = 0; 
            int classes = 1; 
            for(int i = 1; i < s.size(); i++) {
                if(s[_p[i]] != s[_p[i - 1]]) classes++; 
                _c.back()[_p[i]] = classes - 1; 
            }
            
            // Build suffix array and equivalence classes for h > 0 using radix sort
            for(int h = 0; (1 << h) < s.size(); h++) {
                std::vector<int> pn(s.size(), 0); 
                for(int i = 0; i < s.size(); i++) {
                    pn[i] = _p[i] - (1 << h); 
                    if(pn[i] < 0) pn[i] += s.size(); 
                } 
                fill(cnt.begin(), cnt.begin() + classes, 0); 
                for(int i = 0; i < s.size(); i++) cnt[_c.back()[pn[i]]]++; 
                for(int i = 1; i < classes; i++) cnt[i] += cnt[i - 1]; 
                for(int i = s.size()-1; i >= 0; i--) _p[--cnt[_c.back()[pn[i]]]] = pn[i]; 
                std::vector<int> cn (s.size(), 0); 
                cn[_p[0]] = 0; 
                classes = 1; 
                int index = _p[0] + (1 << h); 
                if(index >= s.size()) index -= s.size();
                auto prev = std::make_pair(_c.back()[_p[0]], _c.back()[index]);
                for(int i = 1; i < s.size(); i++) {
                    index = _p[i] + (1 << h); 
                    if(index >= s.size()) index -= s.size(); 
                    auto cur = std::make_pair(_c.back()[_p[i]], _c.back()[index]);
                    if(cur != prev) classes++; 
                    cn[_p[i]] = classes - 1; 
                    cur.swap(prev); 
                }
                _c.push_back(cn); 
            }

            // Build the longest common prefix (LCP) array using kasai's algorithm
            std::vector<int> rank(s.size(), 0); 
            for(int i = 0; i < s.size(); i++) rank[_p[i]] = i; 
            for(int i = 0, k = 0; i < s.size(); i++) {
                if(rank[i] == s.size() - 1) {
                    k = 0; 
                    _lcp[rank[i]] = 0; 
                    continue;  
                }
                int j = _p[rank[i] + 1]; 
                while(i + k < s.size() && j + k < s.size() && s[i + k] == s[j + k]) k++;
                _lcp[rank[i]] = k; 
                if(k) k--;  
            } 
        }
    
        const int &operator[](int i) const {
            return _p[i]; 
        }

        const int &lcp(int i) const {
            return _lcp[i]; 
        }
    
        int compare(int i, int j, int l) {
            int k = 0; 
            while((1 << (k+1)) <= l) k++; 
            auto a = std::make_pair(_c[k][i], _c[k][(i + l - (1 << k)) % _p.size()]);
            auto b = std::make_pair(_c[k][j], _c[k][(j + l - (1 << k)) % _p.size()]);
            return a == b ? 0 : a < b ? -1 : 1; 
        }
    };
}

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
    string s; cin >> s; 
    ttl::SuffixArray sa(s + "$"); 
    ttl::FenwickTree<long long> tree(s.size()); 
    for(int i = 1; i <= s.size(); i++) {
        tree.range_update(sa.lcp(i - 1) + 1, s.size() - sa[i], 1); 
    }
    for(int i = 1; i <= s.size(); i++) {
        cout << tree.query(i) << " "; 
    }
    cout << endl; 
}