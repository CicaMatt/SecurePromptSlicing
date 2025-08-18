import java.nio.ByteBuffer;

public class ChunkCopy {
    public static void main(String[] args) {
        // Allocate the first chunk with some sample data
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        firstChunk.put((byte) 65); // 'A'
        firstChunk.put((byte) 66); // 'B'
        firstChunk.put((byte) 67); // 'C'
        firstChunk.flip(); // Prepare for reading

        // Allocate the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from first chunk to second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip(); // Prepare for reading

        // Print the contents of the second chunk
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
    }
}