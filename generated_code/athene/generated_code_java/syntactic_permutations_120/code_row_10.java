import java.nio.ByteBuffer;

public class ChunkCopy {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define chunk size in bytes

        ByteBuffer chunk1 = ByteBuffer.allocate(chunkSize);
        ByteBuffer chunk2 = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            chunk1.put((byte) i); // Fill the first chunk with some data
        }

        chunk1.flip(); // Prepare for reading from chunk1

        chunk2.put(chunk1); // Copy contents from chunk1 to chunk2

        chunk2.flip(); // Prepare for reading from chunk2

        while (chunk2.hasRemaining()) {
            System.out.print((int) chunk2.get() + " "); // Print the contents of chunk2
        }
    }
}