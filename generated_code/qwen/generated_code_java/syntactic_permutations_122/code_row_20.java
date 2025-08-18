import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Put some data into the first chunk
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to read from the beginning
        firstChunk.rewind();

        // Copy the contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // In Java, we don't explicitly free memory, but we can clear references
        firstChunk = null;
        secondChunk = null;

        // Suggest garbage collector to run (not guaranteed)
        System.gc();
    }
}