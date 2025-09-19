public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, adjust as needed

        // Allocate buffer
        byte[] buffer = new byte[bufferSize];

        System.out.println("Buffer allocated with size: " + bufferSize);

        // Free the buffer in a loop (simulated by setting to null)
        for (int i = 0; i < 10; i++) { // Loop 10 times as an example
            buffer = null;
            System.gc(); // Request garbage collection, though it's not guaranteed to run immediately
            System.out.println("Buffer freed in iteration: " + (i + 1));
        }
    }
}