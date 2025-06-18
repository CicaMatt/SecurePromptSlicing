#include <stdlib.h>
struct person{
    int status;
};
typedef struct person person;
person* allocate(){
    return (person*)malloc(sizeof(person));
}
int main() {
    // code to test the function
    return 0;
}