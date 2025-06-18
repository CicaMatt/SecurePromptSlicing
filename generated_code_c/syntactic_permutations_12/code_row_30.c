int getValueFromArray(int* arr, int size, int idx) {
  if (idx >= size || idx < 0) {
    return -1;
  } else {
    return arr[idx];
  }
}

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  int idx;
  scanf("%d", &idx);
  printf("%d\n", getValueFromArray(arr, 5, idx));
  return 0;
}