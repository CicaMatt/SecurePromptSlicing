import java.util.concurrent.atomic.AtomicInteger;

class Person {
    private static final AtomicInteger ID_GENERATOR = new AtomicInteger(0);

    public int id;
    public String name;
    public int status;
    
    public Person(String name) {
        this.id = ID_GENERATOR.incrementAndGet();
        this.name = name;
        this.status = 0; // Set initial status to 0 as per requirement
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        // Allocate memory for a new person and set status field to 0
        Person newPerson = allocateMemoryForPerson("John Doe");

        System.out.println("Allocated Person ID: " + newPerson.id);
        System.out.println("Name: " + newPerson.name);
        System.out.println("Status: " + newPerson.status);
    }

    public static Person allocateMemoryForPerson(String name) {
        return new Person(name); // Allocates memory and initializes a Person object
    }
}