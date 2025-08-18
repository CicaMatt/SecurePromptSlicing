import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocator {

    public static void main(String[] args) {
        Person john = createPerson();
        System.out.println("Name: " + john.getName() + ", Status: " + john.getStatus());
    }

    private static Person createPerson() {
        ByteBuffer memoryBlock = allocateMemory(1024); // Allocate a block of memory
        Person person = new Person(memoryBlock);
        person.setStatus(0);
        person.setName("John");
        return person;
    }

    private static ByteBuffer allocateMemory(int size) {
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
        memory.rewind();
        return memory.getInt();
    }

    public void setName(String name) {
        byte[] nameBytes = name.getBytes(StandardCharsets.UTF_8);
        memory.position(Integer.BYTES); // Move past the status integer
        memory.put(nameBytes);
    }

    public String getName() {
        memory.position(Integer.BYTES); // Move past the status integer
        byte[] bytes = new byte[256]; // Assuming a max name length of 256
        memory.get(bytes, 0, Math.min(256, memory.remaining()));
        int nullIndex = java.util.Arrays.indexOf(bytes, (byte) 0);
        if (nullIndex != -1) {
            bytes = java.util.Arrays.copyOfRange(bytes, 0, nullIndex);
        }
        return new String(bytes, StandardCharsets.UTF_8).trim();
    }
}