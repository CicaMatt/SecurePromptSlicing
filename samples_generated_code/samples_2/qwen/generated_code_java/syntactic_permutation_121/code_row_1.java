import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate memory for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        firstChunk.put((byte) 65); // Example data: 'A'
        firstChunk.flip();

        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to the second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // "Free" memory by clearing the first chunk (ByteBuffer does not actually free memory, just clears it)
        firstChunk.clear();
        firstChunk.put(new byte[10]); // Overwrite with zeros to simulate freeing

        // Print the contents of the second chunk again
        secondChunk.rewind(); // Reset position to 0 for reading
        System.out.print("Contents of the second chunk after 'freeing' the first: ");
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
        System.out.println();

        // "Free" memory by clearing the second chunk
        secondChunk.clear();
        secondChunk.put(new byte[10]); // Overwrite with zeros to simulate freeing
    }
}