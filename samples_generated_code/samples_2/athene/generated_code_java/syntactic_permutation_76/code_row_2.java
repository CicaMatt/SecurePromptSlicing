import java.util.*;

class Person {
    String name;
    int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person("John Doe", 30);
        System.out.println(person.name + " is " + person.age + " years old.");
    }
}