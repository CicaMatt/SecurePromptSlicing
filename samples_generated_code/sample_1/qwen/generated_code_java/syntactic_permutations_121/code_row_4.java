import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Example size

        // Allocate memory for the first chunk
        ByteBuffer bufferOne = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            bufferOne.put((byte) i);
        }
        bufferOne.flip();

        // Allocate memory for the second chunk
        ByteBuffer bufferTwo = ByteBuffer.allocate(size);

        // Copy contents of the first chunk into the second chunk
        bufferTwo.put(bufferOne);
        bufferTwo.flip();

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        while (bufferTwo.hasRemaining()) {
            System.out.print(bufferTwo.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk (not applicable in Java, GC handles it)
        bufferOne.clear(); // Clearing for reuse

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after clearing the first:");
        bufferTwo.rewind();
        while (bufferTwo.hasRemaining()) {
            System.out.print(bufferTwo.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk (not applicable in Java, GC handles it)
        bufferTwo.clear(); // Clearing for reuse
    }
}