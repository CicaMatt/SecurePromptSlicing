struct Person {
  int id;
  char* name;
  int age;
};
typedef struct Person Person;
Person* create_person(char* name, int age) {
  Person* person = (Person*) malloc(sizeof(Person));
  person->id = 0;
  person->name = name;
  person->age = age;
  return person;
}