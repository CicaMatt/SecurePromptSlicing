import java.nio.ByteBuffer;

public class ChunkCopy {
    public static void main(String[] args) {
        // Create a first chunk with some initial data
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        firstChunk.putInt(123456);
        firstChunk.putChar('A');
        firstChunk.flip();

        // Create a second chunk of the same size as the first
        ByteBuffer secondChunk = ByteBuffer.allocate(firstChunk.capacity());

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Prepare the second chunk for reading
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.println("Integer: " + secondChunk.getInt());
        System.out.println("Char: " + secondChunk.getChar());
    }
}