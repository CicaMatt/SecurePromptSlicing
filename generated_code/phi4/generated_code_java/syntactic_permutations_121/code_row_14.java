import java.nio.ByteBuffer;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print contents of the second chunk
        System.out.println("Contents of second chunk after copy:");
        for (int i = 0; i < secondChunk.capacity(); i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Free memory allocated to first chunk by setting it to null
        firstChunk.clear();
        firstChunk = null;

        // Print contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk:");
        for (int i = 0; i < secondChunk.capacity(); i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by setting it to null
        secondChunk.clear();
        secondChunk = null;
    }
}