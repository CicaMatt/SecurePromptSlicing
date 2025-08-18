import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10; // Size of the chunks

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.rewind();

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy contents from first to second chunk
        buffer2.put(buffer1);
        buffer2.rewind();

        // Print contents of the first chunk
        System.out.println("Contents of the first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print((char) buffer1.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk
        freeBuffer(buffer1);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk
        freeBuffer(buffer2);
    }

    // Method to free direct buffer memory, though in practice this is handled by GC
    private static void freeBuffer(ByteBuffer buffer) {
        if (buffer.isDirect()) {
            ((java.nio.Buffer) buffer).clear();
            sun.misc.Cleaner cleaner = ((sun.nio.ch.DirectBuffer) buffer).cleaner();
            if (cleaner != null) {
                cleaner.clean();
            }
        }
    }
}