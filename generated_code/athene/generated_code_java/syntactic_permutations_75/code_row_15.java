import java.util.Objects;

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
        System.out.println("Person allocated at: " + Objects.hash(person));
    }
}