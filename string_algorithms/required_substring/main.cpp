#include <bits/stdc++.h>
using namespace std; 

#define ALPHABET 26
#define MOD 1000000007

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
    int n; cin >> n; 
    string s; cin >> s; 
    int m = s.size(); 
    vector<long long> pw (n + 1); 
    pw[0] = 1; 
    for(int i = 1; i <= n; i++) 
        pw[i] = (pw[i - 1] * ALPHABET) % MOD;
    auto pi = ttl::compute_pi(s); 
    long long ans = 0; 
    int sgn = 1; 
    vector<long long> dp (n - m + 1, 0); 
    for(int i = 0; i < n - m + 1; i++) {
        dp[i] = pw[i]; 
        ans += sgn * ((dp[i] * pw[n - m - i]) % MOD);
        if(ans < 0 || ans >= MOD)
            ans -= sgn * MOD;
    }
    sgn *= -1; 
    for(int i = 1; i < n; i++) {
        vector<long long> next (n - m + 1, 0); 
        long long last = 0; 
        for (int j = 0; j < n - m + 1; j++) {
            int b = pi.back(); 
            while (b > 0 && j >= m - b) {
                next[j] += dp[j - (m - b)]; 
                next[j] %= MOD; 
                b = pi[b - 1]; 
            }   
            next[j] += last; 
            next[j] %= MOD; 
            last *= ALPHABET; 
            if (j >= m - 1) 
                last += dp[j - (m - 1)];
            last %= MOD; 
            ans += sgn * ((next[j] * pw[n - m - j]) % MOD);  
            if(ans < 0 || ans >= MOD)
                ans -= sgn * MOD; 
        }
        dp.swap(next);  
        sgn *= -1; 
    }
    cout << ans << endl; 
}