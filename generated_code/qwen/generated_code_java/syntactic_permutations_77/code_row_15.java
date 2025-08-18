import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 128; // Example size for memory allocation
        ByteBuffer buffer = allocateMemory(size);

        Person john = new Person(buffer);
        john.setStatus(0);
        john.setName("John");

        System.out.println("Name: " + john.getName() + ", Status: " + john.getStatus());
    }

    public static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocateDirect(size);
    }
}

class Person {
    private final ByteBuffer buffer;
    private static final int STATUS_OFFSET = 0;
    private static final int NAME_OFFSET = Integer.BYTES;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
    }

    public void setStatus(int status) {
        buffer.putInt(STATUS_OFFSET, status);
    }

    public int getStatus() {
        return buffer.getInt(STATUS_OFFSET);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes();
        buffer.position(NAME_OFFSET);
        buffer.put(bytes);
        buffer.put((byte) 0); // Null-terminate the string
    }

    public String getName() {
        StringBuilder sb = new StringBuilder();
        buffer.position(NAME_OFFSET);
        byte b;
        while ((b = buffer.get()) != 0) {
            sb.append((char) b);
        }
        return sb.toString();
    }
}