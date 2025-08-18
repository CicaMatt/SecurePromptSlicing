import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = allocateMemory(10);
        ByteBuffer secondChunk = allocateMemory(10);

        // Copy contents from the first chunk to the second chunk
        copyMemory(firstChunk, secondChunk);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated for the first chunk and print contents of the second chunk again
        freeMemory(firstChunk);
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the second chunk
        freeMemory(secondChunk);

        // Attempting to access or modify the content after freeing should be avoided in real applications
    }

    private static ByteBuffer allocateMemory(int size) {
        return ByteBuffer.allocate(size);
    }

    private static void copyMemory(ByteBuffer source, ByteBuffer destination) {
        for (int i = 0; i < Math.min(source.capacity(), destination.capacity()); i++) {
            destination.put(i, source.get(i));
        }
    }

    private static void freeMemory(ByteBuffer buffer) {
        // In Java, memory is managed by the garbage collector
        // Here we just clear the buffer's position and limit for demonstration purposes.
        buffer.clear();
    }
}