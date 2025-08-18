import java.nio.ByteBuffer;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated with status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.SIZE);
        return new Person(buffer);
    }
}

class Person {
    public static final int SIZE = Integer.BYTES; // Assuming only the status field is stored
    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
        setStatus(0); // Set default status to 0
    }

    public void setStatus(int status) {
        buffer.putInt(status);
    }

    public int getStatus() {
        return buffer.getInt(0);
    }
}