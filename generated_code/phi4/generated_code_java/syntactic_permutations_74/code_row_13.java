class Person {
    int status;
    // Other fields can be added here

    public Person() {
        this.status = 0;  // Initialize status to 0
    }
}

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = new Person();  // Allocate memory for a block of size sizeof(Person)
        System.out.println("Status: " + person.status);  // Should print Status: 0
    }
}