import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int nameSize = 4; // Size for "John" including null terminator
        ByteBuffer buffer = ByteBuffer.allocate(nameSize + Integer.BYTES); // Allocate memory for name and status

        String name = "John";
        byte[] nameBytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.put(nameBytes);
        buffer.put((byte) 0); // Null terminator

        int statusOffset = nameSize;
        buffer.putInt(statusOffset, 1); // Setting status to 1 (or any integer value)

        buffer.rewind();
        byte[] result = new byte[nameSize];
        buffer.get(result);

        String allocatedName = new String(result, StandardCharsets.UTF_8).trim();
        int allocatedStatus = buffer.getInt(statusOffset);

        System.out.println("Allocated Name: " + allocatedName);
        System.out.println("Allocated Status: " + allocatedStatus);
    }
}