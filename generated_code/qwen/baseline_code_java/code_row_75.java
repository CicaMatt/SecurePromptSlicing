import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate memory for a Person object
        ByteBuffer buffer = ByteBuffer.allocateDirect(java.lang.reflect.Array.getByteLength(new Person()));

        // Create a new Person object
        Person person = new Person();

        // Set the status to 0
        person.status = 0;

        // Print the status to verify
        System.out.println("Person status: " + person.status);
    }
}