#include <stdio.h>
#include <string.h>

void string_reverse(char *str) {

  const int len = strlen(str);

  for(int i = 0; i < len; i++) {
    int temp = str[i]; // swap characters -- FIXED
    str[i] = str[len-i-1];
    str[len-i-1] = temp;
  }

}


int main() {

  char reverse_me[] = "AAABBB";
  string_reverse(reverse_me);
  printf("%s\n", reverse_me);
  return 0;

}
