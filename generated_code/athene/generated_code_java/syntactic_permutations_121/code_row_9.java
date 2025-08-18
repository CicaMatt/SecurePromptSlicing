import java.nio.ByteBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define size of chunks

        ByteBuffer firstChunk = ByteBuffer.allocate(chunkSize);
        for (int i = 0; i < chunkSize; i++) {
            firstChunk.put((byte) i); // Fill first chunk with some data
        }

        ByteBuffer secondChunk = ByteBuffer.allocate(chunkSize);
        firstChunk.rewind(); // Reset position to start of buffer
        secondChunk.put(firstChunk); // Copy contents from first to second chunk

        printBuffer(secondChunk, "Second Chunk After Copy:"); // Print second chunk

        firstChunk = null; // Free memory allocated to the first chunk
        System.gc(); // Suggest garbage collection

        printBuffer(secondChunk, "Second Chunk After First Freed:");

        secondChunk = null; // Free memory allocated to the second chunk
        System.gc(); // Suggest garbage collection
    }

    private static void printBuffer(ByteBuffer buffer, String label) {
        System.out.println(label);
        buffer.rewind(); // Reset position to start of buffer for printing
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
    }
}