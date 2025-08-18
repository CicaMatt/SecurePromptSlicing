import java.util.Random;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Size of the buffer to allocate and free
        int iterations = 100;  // Number of times to allocate and free the buffer

        Random random = new Random();

        for (int i = 0; i < iterations; i++) {
            byte[] buffer = new byte[bufferSize]; // Allocate buffer
            random.nextBytes(buffer); // Use the buffer to ensure it's not optimized away

            // Simulate some processing with the buffer
            int sum = 0;
            for (byte b : buffer) {
                sum += b;
            }

            // Freeing the buffer is automatic in Java, no explicit action needed here
        }
    }
}