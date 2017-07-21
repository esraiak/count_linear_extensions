#include "../allt.h"

int N = 11;

vector<pii> cover;
vector<vi> up;
vi down_count;

map<int, int> dp;

vi expand_mask(int mask) {
  vi rt;
  rep(i,0,N) if(mask & (1<<i)) rt.push_back(i+1);
  return rt;
}

int f(int mask) {
  map<int,int>::iterator it = dp.find(mask);
  if(it != dp.end()) return it->second;
  if(mask == (1<<N) - 1) return dp[mask] = 1;
  int rt = 0;
  rep(u,0,N) if(!((1<<u)&mask) && down_count[u] == 0) {
    //add u.
    rep(i,0,up[u].size()) down_count[up[u][i]]--;
    rt += f(mask | (1<<u));
    rep(i,0,up[u].size()) down_count[up[u][i]]++;
  }
  return dp[mask] = rt;
}

int main() {
  //N = 11; vi raw = bb("1 3     2 3    2 4   3 5   3 6    4 6    4 7   5 8    6 8    6 9   7 9    8 10   8 11   9 11"); //pairwise sums of 6 numbers
  //  N = 6; vi raw = bb("1 3    1 4    2 4    3 5   4 5    4 6"); //5 numbers
  N = 17; vi raw = bb("1 3  1 4  2 4    3 5   3 6   4 6   4 7    5 8   5 9   6 9   6 10  7 10   8 11   9 11   9 12  10 12   10 13   11 14  12 14  12 15  13 15   14 16   15 16   15 17");
  //N = 4; vi raw = bb("1 3  2 3  2 4");

  rep(i,0,raw.size()/2) cover.push_back(MP(raw[2*i]-1, raw[2*i+1]-1));

  up.resize(N);
  rep(t,0,cover.size()) up[FI(cover[t])].push_back(SE(cover[t]));

  down_count.resize(N);
  rep(i,0,N) {
    down_count[i] = 0;
    rep(t,0,cover.size()) {
      if(SE(cover[t]) == i) down_count[i]++;
    }
  }
  cout << f(0) << endl;
  return 0;
}
