import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        int personSize = Integer.BYTES; // Assuming 'status' is an integer
        ByteBuffer memoryBlock = allocateMemory(personSize);
        Person newPerson = new Person(memoryBlock);
        newPerson.setStatus(0);
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}

class Person {
    private final ByteBuffer memory;

    public Person(ByteBuffer memory) {
        this.memory = memory;
    }

    public void setStatus(int status) {
        memory.putInt(status);
    }

    public int getStatus() {
        return memory.getInt(0);
    }
}