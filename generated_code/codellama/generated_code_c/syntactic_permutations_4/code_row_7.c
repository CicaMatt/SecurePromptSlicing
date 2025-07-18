int main() {
  char index[10];
  printf("Enter the index of the vehicle you want to print: ");
  scanf("%s", &index);
  int idx = atoi(index);
  Vehicle *vehicles[] = {new Car(), new Boat(), new Truck()};
  vehicles[idx]->print();
}