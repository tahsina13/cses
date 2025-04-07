#include <bits/stdc++.h>
using namespace std; 

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
    auto pi = ttl::compute_pi(s); 
    vector<int> ans; 
    int b = pi.back(); 
    while (b > 0) {
        ans.push_back(b); 
        b = pi[b - 1]; 
    }
    reverse(ans.begin(), ans.end()); 
    for (int x : ans) {
        cout << x << " "; 
    }
    cout << endl; 
}