import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        // Use the allocated person object
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(16); // Assuming sizeof(person) is 16 bytes for this example
        return new Person(buffer);
    }
}

class Person {
    private ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    // Add fields and methods to interact with the byte buffer as needed
}