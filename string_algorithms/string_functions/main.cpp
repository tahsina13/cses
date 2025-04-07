#include <bits/stdc++.h>
using namespace std; 

namespace ttl
{
    /**
     * @brief Computes the Z-array for a given string.
     * 
     * The Z-array for a string s is an array z where z[i] is the length of the longest substring starting from s[i]
     * which is also a prefix of s.
     * 
     * @param s The input string.
     * @return A vector containing the Z-array values.
     */
    vector<int> compute_z_array(const string &s) {
        vector<int> z(s.size());
        int x = 0, y = 0;
        for (int i = 1; i < s.size(); i++) {
            z[i] = max(0, min(z[i-x], y-i+1));
            while (i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) {
                x = i; y = i+z[i]; z[i]++;
            }
        }
        return z; 
    }
}

namespace ttl
{
    /**
     * @brief Computes the prefix function (pi) for a given string.
     * 
     * The prefix function for a string s is an array pi where pi[i] is the length of the longest proper prefix of s[0..i]
     * which is also a suffix of s[0..i].
     * 
     * @param s The input string.
     * @return A vector containing the prefix function values.
     */
    std::vector<int> compute_pi(const std::string &s) {
        std::vector<int> pi (s.size()); 
        int b = 0; 
        for (int i = 1; i < s.size(); i++) {
            while (b > 0 && s[b] != s[i]) {
                b = pi[b - 1];  
            } 
            if (s[b] == s[i]) {
                b++; 
            } 
            pi[i] = b; 
        }    
        return pi; 
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
    string s; cin >> s; 
    auto z = ttl::compute_z_array(s); 
    auto pi = ttl::compute_pi(s); 
    for(int x : z) cout << x << " "; 
    cout << "\n"; 
    for(int x : pi) cout << x << " ";
    cout << "\n";  
}