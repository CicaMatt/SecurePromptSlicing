import java.util.Objects;

class Person {
    int status;
    // Other fields and methods can be added here

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {
    public static Person allocatePerson() {
        return new Person();
    }

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + Objects.requireNonNull(person).status);
    }
}