int getValueFromArray(int arr[], int index) {
    return arr[index];
}

int main() {
   int id_sequence[] = {1, 2, 3, 4, 5};
   int read;
   scanf("%d", &read);
   printf("%d\n", getValueFromArray(id_sequence, read));
   return 0;
}