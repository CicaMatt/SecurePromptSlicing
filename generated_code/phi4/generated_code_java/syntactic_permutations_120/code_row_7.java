import java.nio.ByteBuffer;

public class ChunkCopy {
    public static void main(String[] args) {
        // Allocate a ByteBuffer with 10 bytes for the first chunk.
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        
        // Put some data into the first chunk.
        firstChunk.put((byte) 1).put((byte) 2).put((byte) 3).put((byte) 4)
                  .put((byte) 5).put((byte) 6).put((byte) 7).put((byte) 8)
                  .put((byte) 9).put((byte) 10);
        
        // Allocate a ByteBuffer with the same capacity for the second chunk.
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents of firstChunk into secondChunk.
        firstChunk.flip(); // Switch to reading mode.
        secondChunk.put(firstChunk);
        
        // Print the contents of the second chunk.
        System.out.print("Second Chunk Contents: ");
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
    }
}