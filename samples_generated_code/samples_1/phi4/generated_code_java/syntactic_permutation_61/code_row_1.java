import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Size of the buffer in bytes
        int iterations = 10;   // Number of times to allocate and free the buffer

        for (int i = 0; i < iterations; i++) {
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Perform operations with the buffer if needed
            
            // Buffer is automatically freed when it goes out of scope
        }
        
        System.out.println("Buffer allocated and freed " + iterations + " times.");
    }
}