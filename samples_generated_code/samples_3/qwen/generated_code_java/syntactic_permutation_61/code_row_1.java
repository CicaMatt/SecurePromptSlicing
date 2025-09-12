import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Size of the buffer in bytes

        for (int i = 0; i < 10; i++) { // Loop to allocate and free the buffer 10 times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize); // Allocate a new buffer
            // Use the buffer here if needed...

            // In Java, there is no explicit free method for buffers as memory management is handled by the garbage collector.
            // Setting the reference to null helps the GC reclaim memory faster
            buffer = null;
        }
    }
}