import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define the size of each memory chunk in bytes

        ByteBuffer chunk1 = ByteBuffer.allocate(chunkSize);
        ByteBuffer chunk2 = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            chunk1.put(i, (byte) i); // Fill chunk1 with some data
        }

        chunk1.rewind(); // Reset position to start of buffer for reading

        chunk2.put(chunk1); // Copy contents from chunk1 to chunk2

        chunk1 = null; // Free the first chunk by setting reference to null
        chunk2 = null; // Free the second chunk by setting reference to null

        System.gc(); // Suggest to JVM to perform garbage collection
    }
}