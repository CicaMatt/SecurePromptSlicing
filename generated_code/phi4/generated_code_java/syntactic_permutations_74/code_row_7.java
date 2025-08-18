class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        // Allocate memory for a new person and set status to 0
        Person person = allocateMemory();
        
        // Output the status field of the allocated person
        System.out.println("Status: " + person.status);
    }

    private static Person allocateMemory() {
        Person person = new Person(); // Memory allocation for Person object
        return person;
    }
}