class Person {
    private int id;
    private String name;

    public Person(int id, String name) {
        this.id = id;
        this.name = name;
    }
    
    // Getters and setters for id and name can be added here if needed
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = (Person) allocateMemory();
        
        // Example usage: initializing the allocated memory
        person = new Person(1, "John Doe");

        System.out.println("Allocated and initialized a Person object.");
    }

    public static Object allocateMemory() {
        Person person = new Person(0, "");  // Allocate memory for a Person object with initial values
        return person;
    }
}