import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class Main {
    public static void main(String[] args) {
        int size = Integer.BYTES + 4 * "John".getBytes(StandardCharsets.UTF_8).length; // Status (int) + Name (String)
        ByteBuffer memoryBlock = allocateMemory(size);

        // Set status to 0
        memoryBlock.putInt(0);

        // Set name to "John"
        byte[] nameBytes = "John".getBytes(StandardCharsets.UTF_8);
        memoryBlock.put(nameBytes);

        // Reset position for reading
        memoryBlock.rewind();

        // Read and print status
        int status = memoryBlock.getInt();
        System.out.println("Status: " + status);

        // Read and print name
        byte[] readNameBytes = new byte[nameBytes.length];
        memoryBlock.get(readNameBytes);
        String name = new String(readNameBytes, StandardCharsets.UTF_8);
        System.out.println("Name: " + name);
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }
}