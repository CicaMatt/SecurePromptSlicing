import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define the size of memory chunks

        ByteBuffer buffer1 = ByteBuffer.allocate(chunkSize);
        for (int i = 0; i < chunkSize; i++) {
            buffer1.put((byte) i); // Fill buffer1 with some data
        }

        ByteBuffer buffer2 = ByteBuffer.allocate(chunkSize);
        buffer1.flip(); // Prepare buffer1 for reading

        buffer2.put(buffer1); // Copy contents from buffer1 to buffer2

        buffer1 = null; // Free the first chunk by setting reference to null
        buffer2 = null; // Free the second chunk by setting reference to null

        System.gc(); // Request garbage collection to free memory
    }
}