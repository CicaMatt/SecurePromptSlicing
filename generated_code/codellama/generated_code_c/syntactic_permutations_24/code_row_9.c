int main() {
  int a = rand() % 99 + 10;
  int b = rand() % 99 + 10;
  int c = a - b;
  printf("%d - %d = %d\n", a, b, c);
  return 0;
}