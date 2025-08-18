import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) (i + 1));
        }
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print the contents of the second chunk
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk by letting it go out of scope
        firstChunk = null;

        // Explicitly suggest garbage collection (though not guaranteed)
        System.gc();

        // Print the contents of the second chunk again
        System.out.println("Second Chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk by letting it go out of scope
        secondChunk = null;

        // Explicitly suggest garbage collection (though not guaranteed)
        System.gc();
    }
}