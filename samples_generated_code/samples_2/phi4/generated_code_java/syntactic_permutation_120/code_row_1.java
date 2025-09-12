import java.nio.ByteBuffer;

public class ChunkCopy {
    public static void main(String[] args) {
        // Create two ByteBuffer instances with a capacity of 10 bytes each.
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Put some sample data into the first chunk.
        for (int i = 0; i < 5; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Reset position to start copying from the beginning of firstChunk
        firstChunk.flip();

        // Copy contents from the first chunk to the second chunk.
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Reset the buffer to read data from the beginning
        secondChunk.flip();

        // Print the contents of the second chunk.
        byte[] array = new byte[secondChunk.remaining()];
        secondChunk.get(array);
        System.out.println(new String(array));
    }
}