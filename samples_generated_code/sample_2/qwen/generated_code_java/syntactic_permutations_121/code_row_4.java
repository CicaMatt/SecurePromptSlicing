import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate memory for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        
        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }
        
        // Reset position to start reading from the beginning
        firstChunk.rewind();
        
        // Allocate memory for the second chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(size);
        
        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);
        
        // Reset position to start reading from the beginning
        secondChunk.rewind();
        
        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        for (int i = 0; i < size; i++) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();
        
        // Clear the first chunk, effectively freeing its memory in this context
        firstChunk.clear();
        
        // Reset position to start reading from the beginning
        secondChunk.rewind();
        
        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after clearing the first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print((char) secondChunk.get() + " ");
        }
        System.out.println();
        
        // Clear the second chunk, effectively freeing its memory in this context
        secondChunk.clear();
    }
}