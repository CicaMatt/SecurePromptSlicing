import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Create a byte buffer with enough capacity
        ByteBuffer buffer = ByteBuffer.allocate(10);

        // Define the source bytes (string "Hello")
        byte[] sourceBytes = "Hello".getBytes();

        // Perform memory copy from source to buffer starting at position 0
        copyMemory(buffer, 0, sourceBytes, 5);

        // Convert buffer back to string and print it
        System.out.println(new String(buffer.array()).trim());
    }

    public static void copyMemory(ByteBuffer destination, int destPosition, byte[] source, int length) {
        for (int i = 0; i < length; i++) {
            destination.put(destPosition + i, source[i]);
        }
    }
}