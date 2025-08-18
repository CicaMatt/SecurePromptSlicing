import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        Person person = allocatePerson();
        person.setStatus(1); // Assuming 1 means active or some other status
    }

    private static Person allocatePerson() {
        ByteBuffer buffer = ByteBuffer.allocateDirect(Person.sizeOf());
        IntBuffer intBuffer = buffer.asIntBuffer();
        return new Person(intBuffer);
    }
}

class Person {
    private final IntBuffer buffer;
    public static final int SIZE_OF_INT = 4; // Size of an integer in bytes
    public static final int STATUS_OFFSET = 0;

    public Person(IntBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.put(STATUS_OFFSET, status);
    }

    public int getStatus() {
        return buffer.get(STATUS_OFFSET);
    }

    public static int sizeOf() {
        // Assuming person has only one integer field for status
        return SIZE_OF_INT;
    }
}