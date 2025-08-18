import java.util.Arrays;

class Person {
    int status;
    // Other fields can be added here

    public Person() {
        this.status = 0;
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = Person.allocatePerson();
        System.out.println("Status: " + person.status);
    }
}