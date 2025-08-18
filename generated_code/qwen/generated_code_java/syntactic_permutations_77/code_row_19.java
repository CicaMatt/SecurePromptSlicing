import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int ageSize = Integer.BYTES; // Size of an integer in bytes
        int nameSize = 4 * "John".length(); // Assuming each character is 4 bytes (UTF-16)
        int totalSize = ageSize + nameSize;

        ByteBuffer buffer = ByteBuffer.allocate(totalSize);

        // Set age to 0
        buffer.putInt(0);

        // Set name to "John"
        byte[] nameBytes = "John".getBytes(StandardCharsets.UTF_16);
        buffer.put(nameBytes);

        buffer.rewind();

        int allocatedAge = buffer.getInt();
        byte[] allocatedNameBytes = new byte[nameSize];
        buffer.get(allocatedNameBytes);

        String allocatedName = new String(allocatedNameBytes, StandardCharsets.UTF_16).trim();

        System.out.println("Allocated Age: " + allocatedAge);
        System.out.println("Allocated Name: " + allocatedName);
    }
}