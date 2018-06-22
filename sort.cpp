#include<cstdio>
#include<cstring>

const int MAX_NUM = 1e5;

int arr[MAX_NUM];
int num;

void sort(int *arr, int len) {
  static int buf[MAX_NUM];
  int cnt[4][256];
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 256; ++j) {
      cnt[i][j] = 0;
    }
  }
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < len; ++j) {
      ++cnt[i][(arr[j] >> (i << 3)) & 255];
    }
  }
  int *a = arr;
  int *b = buf;
  int local[256];
  for(int i = 0; i < 4; ++i) {
    int loc = -1;
    for(int j = 0; j < 256; ++j) {
      local[j] = loc;
      loc += cnt[i][j];
    }
    for(int j = 0; j < len; ++j) {
      b[++local[(a[j] >> (i << 3)) & 255]] = a[j];
    }
    int *c = a;
    a = b;
    b = c;
  }
  return;
}


int main() {
  scanf("%d", &num);
  for(int i = 0; i < num; ++i) {
    scanf("%d", arr + i);
  }
  sort(arr, num);
  for(int i = 0; i < num; ++i) {
    printf("%d ", arr[i]);
  }
  
  return 0;
}
