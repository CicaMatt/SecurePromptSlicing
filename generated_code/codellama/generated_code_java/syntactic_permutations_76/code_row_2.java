java

import java.util.*;

class Person {
    int age;
    String name;
}

public class Main {
    
	static Person *malloc(int n) {
        return new Person[n];
    }
  
    public static void main(String[] args) {
        
        Person *ptr = malloc(1);  // allocates memory for one person
        ptr -> age=25;            // sets the age to 25
        ptr -> name="John";       // sets the name to "john"
    }
}