import java.util.*;

public class Person {
    public int age;
    public char gender;
}

public static void main(String[] args) {
    // Create an object of the Person class 
    Person p = new Person();

    // Set age and gender of the person
    p.age = 30;
    p.gender = 'M';
}

public static void main(String[] args) {
    // Creating a pointer object to store the starting address of the block
    Person p = malloc(sizeof(Person));

    // Set age and gender of the person
    p.age = 30;
    p.gender = 'M';
}