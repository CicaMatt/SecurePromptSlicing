public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        byte[] buffer;

        for (int i = 0; i < 10; i++) { // Example loop to allocate and free the buffer 10 times
            buffer = new byte[bufferSize]; // Allocate buffer
            buffer = null; // Free buffer by dereferencing it
            System.gc(); // Suggest garbage collection, though not guaranteed to run immediately
        }
    }
}