import java.util.Objects;

class Person {
    String name;
    int age;

    public Person() {}
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Memory allocated for person: " + Objects.hash(person));
    }
}