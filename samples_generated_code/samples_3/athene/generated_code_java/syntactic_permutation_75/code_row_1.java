import java.util.Objects;

class Person {
    String name;
    int age;
    boolean status;

    public Person() {
        this.status = false; // Assuming the default status is false as per the request
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = new Person();
        System.out.println("Person allocated at: " + Objects.hash(person));
        System.out.println("Status set to: " + person.status);
    }
}