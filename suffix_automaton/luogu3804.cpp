#include <bits/stdc++.h>
using namespace std;
struct state {
    int len, link;
    std::map<char, int> nxt;
};
const int maxn = 100007;
int ans;
state st[maxn * 2];
int len[maxn], siz[maxn];
int sz, last;
void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz = 1;
    last = 0;
}
void sam_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1, siz[cur] = 1;
    int p = last;
    while (p != -1 && !st[p].nxt.count(c)) {
        st[p].nxt[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].nxt[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].nxt = st[q].nxt;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].nxt[c] == q) {
                st[p].nxt[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
void dfs(int x) {
    dbg(x);
    for (auto i : st[x].nxt) {
        dfs(i.second);
        siz[x] += siz[i.second];
    }
    if (siz[x] > 1) ans = max(ans, siz[x] * st[x].len);
}
int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
        sam_extend(s[i]);
    ans = 0;
    dfs(1);
    cout << ans;
}