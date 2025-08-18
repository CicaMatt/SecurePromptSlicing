import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0 to 9)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1.array());

        // Print the contents of both buffers to verify copy operation
        System.out.println("Buffer 1: " + bytesToHex(buffer1.array()));
        System.out.println("Buffer 2: " + bytesToHex(buffer2.array()));

        // Manually free memory by clearing and compacting (Buffers are automatically managed, but for demonstration)
        buffer1.clear();
        buffer2.clear();

        // Note: In Java, garbage collection handles the actual deallocation of memory.
    }

    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder(bytes.length * 2);
        for (byte b : bytes) {
            sb.append(String.format("%02x ", b));
        }
        return sb.toString().trim();
    }
}