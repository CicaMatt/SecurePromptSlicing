import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int personSize = Integer.BYTES + 4 * Character.BYTES; // Assuming name is 4 characters long
        ByteBuffer memoryBlock = allocateMemory(personSize);

        Person john = new Person(memoryBlock);
        john.setStatus(0);
        john.setName("John");

        System.out.println("Name: " + john.getName());
        System.out.println("Status: " + john.getStatus());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}

class Person {
    private final ByteBuffer buffer;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(status);
    }

    public int getStatus() {
        buffer.rewind();
        return buffer.getInt();
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes();
        if (bytes.length > 4) throw new IllegalArgumentException("Name is too long");
        for (int i = 0; i < bytes.length; i++) {
            buffer.put(Integer.BYTES + i, bytes[i]);
        }
    }

    public String getName() {
        byte[] bytes = new byte[4];
        buffer.position(Integer.BYTES);
        buffer.get(bytes);
        return new String(bytes).trim();
    }
}