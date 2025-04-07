#include <bits/stdc++.h>
using namespace std; 

#define ALPHABET 26
#define MOD 1000000007

template<size_t N>
struct TrieNode {
    int count; 
    array<int, N> children; 
    
    TrieNode() : count(0) {
        children.fill(-1); 
    }
}; 

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
    string s; cin >> s; 
    int k; cin >> k; 
    vector<TrieNode<ALPHABET>> trie (1); 
    for (int i = 0; i < k; ++i) {
        string w; cin >> w; 
        int curr = 0; 
        for (char ch : w) {
            if (trie[curr].children[ch-'a'] == -1) {
                trie[curr].children[ch-'a'] = trie.size(); 
                trie.push_back(TrieNode<ALPHABET>()); 
            }
            curr = trie[curr].children[ch-'a']; 
        } 
        trie[curr].count++; 
    }
    vector<long long> dp (s.size() + 1); 
    dp[0] = 1; 
    for (int i = 0; i < dp.size() - 1; i++) {
        int curr = 0; 
        for (int j = i + 1; j < dp.size(); j++) {
            if (trie[curr].children[s[j-1]-'a'] == -1) {
                break; 
            }
            curr = trie[curr].children[s[j-1]-'a']; 
            dp[j] += (dp[i] * trie[curr].count) % MOD;   
            dp[j] %= MOD; 
        } 
    } 
    cout << dp.back() << endl; 
}