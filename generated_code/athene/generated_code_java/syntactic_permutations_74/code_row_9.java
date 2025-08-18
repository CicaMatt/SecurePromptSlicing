import java.util.Arrays;

class Person {
    int status;
    // other fields can be added here

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Allocated person with status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person();
    }
}