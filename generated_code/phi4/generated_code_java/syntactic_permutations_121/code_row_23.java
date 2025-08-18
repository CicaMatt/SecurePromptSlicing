import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        int size = 10; // Define the size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with example data (e.g., integers from 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk before freeing memory:");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Manually free the first chunk by discarding it, as ByteBuffer doesn't provide explicit free
        firstChunk = null;

        // Print the contents of the second chunk again after freeing the first chunk's memory
        System.out.println("Contents of the second chunk after freeing memory from the first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get(i) + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk by discarding it
        secondChunk = null;

        // Attempting to access the contents of the freed second chunk will result in an error if uncommented
        // System.out.println("Contents of the second chunk after freeing its own memory:");
        // for (int i = 0; i < size; i++) {
        //     System.out.print(secondChunk.get(i) + " ");
        // }
        // System.out.println();

    }

}