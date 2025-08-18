import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate memory for two chunks, each of size 10 bytes
        ByteBuffer chunkOne = ByteBuffer.allocate(10);
        ByteBuffer chunkTwo = ByteBuffer.allocate(10);

        // Put some data into the first chunk
        String data = "1234567890";
        byte[] dataArray = data.getBytes();
        chunkOne.put(dataArray);

        // Reset position to start of the buffer before reading or copying
        chunkOne.rewind();

        // Copy contents from the first chunk to the second chunk
        chunkTwo.put(chunkOne.array(), 0, chunkOne.limit());

        // Freeing memory in Java is automatic via garbage collection,
        // but we can help by dereferencing objects that are no longer needed.
        chunkOne = null;
        chunkTwo = null;

        // Suggest to JVM to run Garbage Collector
        System.gc();
    }
}