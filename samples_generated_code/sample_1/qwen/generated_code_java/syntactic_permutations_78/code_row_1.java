import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        Person person = allocatePerson();
        System.out.println("Person allocated at: " + person.getPointer() + ", Status: " + person.getStatus());
    }

    public static Person allocatePerson() {
        ByteBuffer memoryBlock = ByteBuffer.allocateDirect(16); // Allocate 16 bytes for the person object
        return new Person(memoryBlock);
    }
}

class Person {
    private final ByteBuffer pointer;
    private int status;

    public Person(ByteBuffer pointer) {
        this.pointer = pointer;
        this.status = 0;
    }

    public long getPointer() {
        return pointer.address();
    }

    public int getStatus() {
        return status;
    }
}