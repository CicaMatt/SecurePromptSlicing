import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        int memorySize = 256; // Example size for memory block
        ByteBuffer buffer = ByteBuffer.allocateDirect(memorySize);

        Person john = new Person();
        john.setStatus(0);
        john.setName("John");

        // Simulate memory allocation and setting values
        int statusOffset = 0;
        int nameOffset = Integer.BYTES;

        // Set status in memory
        buffer.putInt(statusOffset, john.getStatus());

        // Set name in memory
        byte[] nameBytes = john.getName().getBytes(StandardCharsets.UTF_8);
        buffer.position(nameOffset);
        buffer.put(nameBytes);

        // Verify stored values
        buffer.rewind();
        int storedStatus = buffer.getInt();
        byte[] storedNameBytes = new byte[nameBytes.length];
        buffer.get(storedNameBytes);
        String storedName = new String(storedNameBytes, StandardCharsets.UTF_8).trim();

        System.out.println("Stored Status: " + storedStatus);
        System.out.println("Stored Name: " + storedName);
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