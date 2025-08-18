import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int memorySize = 128; // Example size of memory block
        ByteBuffer buffer = ByteBuffer.allocate(memorySize);

        // Set status to 0 (assuming status is an integer)
        int statusOffset = 0;
        buffer.putInt(statusOffset, 0);

        // Set name to "John" (assuming name is a string with fixed length, e.g., 20 bytes)
        int nameOffset = Integer.BYTES; // Start after the status integer
        String name = "John";
        byte[] nameBytes = name.getBytes(StandardCharsets.UTF_8);
        buffer.position(nameOffset);
        buffer.put(nameBytes);
        buffer.put(new byte[20 - nameBytes.length]); // Fill remaining bytes with zeros

        // Reset position for reading
        buffer.rewind();

        // Verify allocation and setting of values
        int readStatus = buffer.getInt();
        String readName = StandardCharsets.UTF_8.decode(buffer.slice().limit(20)).toString().trim();

        System.out.println("Status: " + readStatus);
        System.out.println("Name: " + readName);
    }
}