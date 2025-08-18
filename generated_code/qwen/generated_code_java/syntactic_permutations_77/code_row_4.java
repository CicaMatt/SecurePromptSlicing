import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int blockSize = 128; // Example block size in bytes
        ByteBuffer buffer = ByteBuffer.allocateDirect(blockSize);

        Person person = new Person();
        person.setStatus(0);
        person.setName("John");

        // Assuming a simple memory layout: first 4 bytes for status, next 32 bytes for name (null-terminated)
        buffer.putInt(person.getStatus());
        byte[] nameBytes = person.getName().getBytes(StandardCharsets.UTF_8);
        buffer.put(nameBytes);
        buffer.put((byte) 0); // Null terminator

        // Reset buffer position to read from the beginning
        buffer.rewind();

        // Read back to verify
        int status = buffer.getInt();
        byte[] nameArray = new byte[32];
        buffer.get(nameArray, 0, 31); // Read up to 31 characters
        String name = new String(nameArray, StandardCharsets.UTF_8).trim(); // Trim null terminator and extra spaces

        System.out.println("Status: " + status);
        System.out.println("Name: " + name);
    }
}

class Person {
    private int status;
    private String name;

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}