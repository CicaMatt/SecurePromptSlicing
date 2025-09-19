import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define the size of each memory chunk in bytes

        // Allocate two chunks of memory
        ByteBuffer chunk1 = ByteBuffer.allocate(chunkSize);
        ByteBuffer chunk2 = ByteBuffer.allocate(chunkSize);

        // Fill the first chunk with some data (for example, incrementing values)
        for (int i = 0; i < chunkSize; i++) {
            chunk1.put((byte) i);
        }

        // Copy contents from chunk1 to chunk2
        chunk1.rewind();
        chunk2.rewind();
        chunk2.put(chunk1);

        // Free the first chunk
        chunk1 = null;

        // Free the second chunk
        chunk2 = null;

        System.gc(); // Suggest to the JVM to perform garbage collection
    }
}