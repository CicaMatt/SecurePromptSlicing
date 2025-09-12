import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }
        
        // Copy contents of the first chunk to a new array
        byte[] copyArray = new byte[size];
        buffer1.rewind();
        buffer1.get(copyArray);
        
        // Print contents of the copied array
        System.out.println("Contents of the first chunk (copied):");
        for (byte b : copyArray) {
            System.out.print(b + " ");
        }
        System.out.println();
        
        // Free memory allocated to the first chunk by letting it be garbage collected
        buffer1 = null;
        System.gc(); // Suggestion to JVM to run GC
        
        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            buffer2.put((byte) (i * 2));
        }
        
        // Print contents of the second chunk
        System.out.println("Contents of the second chunk:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();
        
        // Free memory allocated to the second chunk by letting it be garbage collected
        buffer2 = null;
        System.gc(); // Suggestion to JVM to run GC
    }
}