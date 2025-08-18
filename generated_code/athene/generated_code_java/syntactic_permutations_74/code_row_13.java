import java.util.Objects;

class Person {
    int status;
    // other fields

    public Person() {
        this.status = 0;
    }

    public static Person allocatePerson() {
        return new Person();
    }
}

public class MemoryAllocationDemo {
    public static void main(String[] args) {
        Person person = Person.allocatePerson();
        System.out.println("Status: " + Objects.requireNonNull(person).status);
    }
}