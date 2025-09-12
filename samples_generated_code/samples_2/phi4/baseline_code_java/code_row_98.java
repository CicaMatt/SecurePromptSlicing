import java.nio.ByteBuffer;

class Person {
    int age;
    String name;
    int status; // Status field

    public Person() {
        this.status = 0; // Initialize status to 0
    }
}

public class MemoryAllocator {

    private static final int PERSON_SIZE = 4 + Integer.BYTES + Integer.BYTES * 2 + 1;

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Status: " + person.status); // Should print 0
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocate(PERSON_SIZE);
        int offset = 4; // Skip the integer size placeholder

        // Allocate space for 'age' and 'status'
        buffer.putInt(offset, 0); 
        offset += Integer.BYTES;
        buffer.putInt(offset, 0); 
        offset += Integer.BYTES;

        // Placeholder for string name (null-terminated)
        buffer.put(offset, '\0'); 
        offset++;

        return new Person();
    }
}