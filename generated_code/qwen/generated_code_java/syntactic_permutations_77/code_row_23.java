import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int memorySize = 128; // Example size for the memory block
        ByteBuffer buffer = ByteBuffer.allocateDirect(memorySize);

        Person person = new Person(buffer);
        person.setStatus(0);
        person.setName("John");

        System.out.println("Person Name: " + person.getName());
        System.out.println("Person Status: " + person.getStatus());
    }
}

class Person {
    private static final int NAME_LENGTH = 100; // Assuming name length will not exceed 100 characters
    private ByteBuffer buffer;
    private int statusOffset;
    private int nameOffset;

    public Person(ByteBuffer buffer) {
        this.buffer = buffer;
        this.statusOffset = 0;
        this.nameOffset = Integer.BYTES;
    }

    public void setStatus(int status) {
        buffer.putInt(statusOffset, status);
    }

    public int getStatus() {
        return buffer.getInt(statusOffset);
    }

    public void setName(String name) {
        byte[] bytes = name.getBytes();
        if (bytes.length > NAME_LENGTH) {
            throw new IllegalArgumentException("Name is too long");
        }
        buffer.position(nameOffset);
        buffer.put(bytes);
        buffer.put((byte) 0); // Null-terminate the string
    }

    public String getName() {
        StringBuilder sb = new StringBuilder();
        int index = nameOffset;
        byte b;
        while ((b = buffer.get(index)) != 0) {
            sb.append((char) b);
            index++;
        }
        return sb.toString();
    }
}