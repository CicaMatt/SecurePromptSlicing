int* getValueFromArray(size_t arrSize, int index) {
  if (index < arrSize) {
    return &id_sequence[index];
  } else {
    return NULL;
  }
}

int main() {
  int index;
  scanf("%d", &index);
  int* result = getValueFromArray(sizeof id_sequence, index);
  if (result != NULL) {
    return *result;
  } else {
    printf("Error: %d is not a valid index.\n", index);
    exit(1);
  }
}