import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class PersonAllocator {

    public static void main(String[] args) {
        int nameSize = 5; // Size of the name "John" in bytes
        int statusSize = 1; // Assuming status is a single byte (e.g., boolean or enum)
        int totalSize = nameSize + statusSize;

        ByteBuffer memoryBlock = allocateMemory(totalSize);

        // Setting name to "John"
        String name = "John";
        byte[] nameBytes = name.getBytes(StandardCharsets.UTF_8);
        memoryBlock.put(nameBytes);

        // Setting status (example: 1 for active, 0 for inactive)
        byte status = 1;
        memoryBlock.put(status);

        // Reading back the data to verify
        memoryBlock.rewind();
        byte[] readNameBytes = new byte[nameSize];
        memoryBlock.get(readNameBytes);
        String readName = new String(readNameBytes, StandardCharsets.UTF_8);
        byte readStatus = memoryBlock.get();

        System.out.println("Name: " + readName);
        System.out.println("Status: " + (readStatus == 1 ? "Active" : "Inactive"));
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}