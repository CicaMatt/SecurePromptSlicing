import java.nio.ByteBuffer;

public class MemoryManipulation {
    public static void main(String[] args) {
        // Allocate memory for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(16);
        firstChunk.put("HelloWorld".getBytes());

        // Reset position to start reading from the beginning
        firstChunk.flip();

        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(16);

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Reset position to start reading from the beginning
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + new String(secondChunk.array(), 0, secondChunk.limit()));

        // Free memory allocated to the first chunk by nullifying reference
        firstChunk = null;

        // Reset position to start reading from the beginning
        secondChunk.flip();

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first: " + new String(secondChunk.array(), 0, secondChunk.limit()));

        // Free memory allocated to the second chunk by nullifying reference
        secondChunk = null;
    }
}