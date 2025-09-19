public class Person {
    int status;
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status);
    }

    public static Person allocatePerson() {
        return new Person(); // Allocates a block of memory for a person and sets default status to 0
    }
}