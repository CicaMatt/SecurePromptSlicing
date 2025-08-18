import java.nio.ByteBuffer;

class Person {
    int status;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = allocateMemory(sizeof(new Person()));
        Person person = newPerson(buffer);
        person.status = 0;
    }

    private static int sizeof(Person person) {
        return Integer.BYTES; // Assuming only the status field is present
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }

    private static Person newPerson(ByteBuffer buffer) {
        Person person = new Person();
        buffer.rewind();
        buffer.putInt(person.status); // Initialize with default value of status
        buffer.rewind();
        return person;
    }
}