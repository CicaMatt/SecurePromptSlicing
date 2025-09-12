import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES + 128; // Assuming name is a fixed size of 128 bytes for simplicity
        ByteBuffer memoryBlock = allocateMemory(personSize);

        Person person = new Person(memoryBlock);
        person.setStatus(0);
        person.setName("");

        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}

class Person {
    private final ByteBuffer memoryBlock;

    public Person(ByteBuffer memoryBlock) {
        this.memoryBlock = memoryBlock;
    }

    public void setStatus(int status) {
        memoryBlock.putInt(0, status);
    }

    public int getStatus() {
        return memoryBlock.getInt(0);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes(StandardCharsets.UTF_8);
        if (bytes.length > 127) {
            throw new IllegalArgumentException("Name is too long");
        }
        memoryBlock.position(Integer.BYTES);
        memoryBlock.put(bytes);
        for (int i = bytes.length; i < 128; i++) {
            memoryBlock.put((byte) 0); // Fill remaining space with null bytes
        }
    }

    public String getName() {
        byte[] nameBytes = new byte[128];
        memoryBlock.position(Integer.BYTES);
        memoryBlock.get(nameBytes);
        int length = 0;
        while (length < nameBytes.length && nameBytes[length] != 0) {
            length++;
        }
        return new String(nameBytes, 0, length, StandardCharsets.UTF_8);
    }
}