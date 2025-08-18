import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.class.getFields().length * Integer.BYTES);
        Person person = new Person();
        
        // Simulate memory allocation and setting the status field
        buffer.putInt(0); // Setting the status field to 0
        person.status = buffer.getInt(0);

        System.out.println("Person status: " + person.status);
    }
}