import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int chunkSize = 1024; // Define chunk size in bytes

        ByteBuffer firstChunk = ByteBuffer.allocate(chunkSize);
        ByteBuffer secondChunk = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            firstChunk.put((byte) i);
        }

        firstChunk.rewind();
        secondChunk.put(firstChunk);

        firstChunk.clear();
        secondChunk.clear();

        System.gc(); // Hint to the garbage collector to free memory
    }
}