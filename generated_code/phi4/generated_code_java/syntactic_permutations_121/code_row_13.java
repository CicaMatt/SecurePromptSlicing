import java.nio.ByteBuffer;

public class MemoryCopyDemo {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Put some data into the first chunk
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) (i + 1));
        }
        firstChunk.flip();

        // Copy contents from the first chunk to the second chunk
        firstChunk.get(secondChunk.array());

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        for (int i = 0; i < 10; i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by compacting it
        firstChunk.clear();

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk:");
        for (int i = 0; i < 10; i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by compacting it
        secondChunk.clear();
    }
}