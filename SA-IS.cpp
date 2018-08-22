#include<cstdio>
#include<cstring>

const int MAX_LEN = 1e6 + 5;

enum type_t{L = 0, S};
int sa[MAX_LEN];
bool isLMS(type_t *type, int loc) {
  if(loc <= 0) return false;
  if(type[loc] != S) return false;
  if(type[loc - 1] != L) return false;
  return true;
}
template<typename T>
bool sameLMS(T str, type_t *type, int i, int j) {
  if(i == -1 || j == -1) return false;
  int k = -1;
  while(true) {
    ++k;
    if(str[i + k] != str[j + k]) return false;
    if(type[i + k] != type[j + k]) return false;
    if(k == 0) continue;
    if(isLMS(type, i + k) != isLMS(type, j + k)) return false;
    if(isLMS(type, i + k)) break;
  }
  return true;
}
template<typename T>
void inducedSort(T str, int len, int sigma, type_t *type, int *LMS, int LMSSize) {
  int *bucket = new int[sigma];
  int *buf = new int[sigma];
  memset(sa, -1, sizeof(sa[0]) * len);
  memset(bucket, 0, sizeof(bucket[0]) * sigma);
  for(int i = 0; i < len; ++i) {
    ++bucket[str[i]];
  }
  buf[0] = bucket[0];
  for(int i = 1; i < sigma; ++i) {
    buf[i] = buf[i - 1] + bucket[i];
  }
  for(int i = LMSSize - 1; i >= 0; --i) {
    sa[--buf[str[LMS[i]]]] = LMS[i];
  }
  
  buf[0] = 0;
  for(int i = 1; i < sigma; ++i) {
    buf[i] = buf[i - 1] + bucket[i - 1];
  }
  for(int i = 0; i < len; ++i) {
    if(sa[i] <= 0) continue;
    if(type[sa[i] - 1] != L) continue;
    sa[buf[str[sa[i] - 1]]++] = sa[i] - 1;
  }
  
  buf[0] = bucket[0];
  for(int i = 1; i < sigma; ++i) {
    buf[i] = buf[i - 1] + bucket[i];
  }
  for(int i = len - 1; i >= 0; --i) {
    if(sa[i] <= 0) continue;
    if(type[sa[i] - 1] != S) continue;
    sa[--buf[str[sa[i] - 1]]] = sa[i] - 1;
  }
  delete[] bucket;
  delete[] buf;
  return;
}
template<typename T>
void sais(T str, int len, int sigma, int *LMS) {
  type_t *type = new type_t[len];
  type[len - 1] = S;
  for(int i = len - 2; i >= 0; --i) {
    type[i] = str[i] < str[i + 1] ? S : L;
    if(str[i] != str[i + 1]) continue;
    type[i] = type[i + 1];
  }
  
  int LMSSize = 0;
  for(int i = 0; i < len; ++i) {
    if(!isLMS(type, i)) continue;
    LMS[LMSSize++] = i;
  }
  
  inducedSort(str, len, sigma, type, LMS, LMSSize);
  int pre = -1;
  int cnt = 0;
  int *temp = new int[len];
  for(int i = 0; i < len; ++i) {
    if(!isLMS(type, sa[i])) continue;
    if(!sameLMS(str, type, pre, sa[i])) ++cnt;
    temp[sa[i]] = cnt - 1;
    pre = sa[i];
  }
  int *s1 = new int[LMSSize];
  LMSSize = 0;
  for(int i = 0; i < len; ++i) {
    if(!isLMS(type, i)) continue;
    s1[LMSSize++] = temp[i];
  }
  delete[] temp;
  
  int *nextLMS = new int[LMSSize];
  if(cnt < LMSSize) {
    sais(s1, LMSSize, cnt, nextLMS);
  } else {
    for(int i = 0; i < LMSSize; ++i) {
      sa[s1[i]] = i;
    }
  }
  delete[] s1;
  for(int i = 0; i < LMSSize; ++i) {
    nextLMS[i] = LMS[sa[i]];
  }
  
  inducedSort(str, len, sigma, type, nextLMS, LMSSize);
  delete[] nextLMS;
  delete[] type;
  return;
}

char str[MAX_LEN];

int main() {
  scanf("%s", str);
  int len = strlen(str);
  int *LMS = new int[len];
  sais(str, len + 1, 256, LMS);
  delete[] LMS;
  for(int i = 1; i <= len; ++i) {
    printf("%d ", sa[i] + 1);
  }
  return 0;
}
