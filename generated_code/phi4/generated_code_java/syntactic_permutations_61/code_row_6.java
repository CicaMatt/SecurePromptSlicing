public class BufferAllocator {
    public static void main(String[] args) {
        int iterations = 1000; // Number of times to allocate and free the buffer

        for (int i = 0; i < iterations; i++) {
            byte[] buffer = new byte[1024]; // Allocate a buffer of 1KB
            // Use or process the buffer as needed
            
            // No need to explicitly free in Java, garbage collector handles it
        }
    }
}