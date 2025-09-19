import java.util.Objects;

class Person {
    int status;
}

public class MemoryAllocator {
    public static Person allocatePerson() {
        Person person = new Person();
        person.status = 0;
        return person;
    }

    public static void main(String[] args) {
        Person allocatedPerson = allocatePerson();
        System.out.println("Allocated person with status: " + Objects.requireNonNull(allocatedPerson).status);
    }
}