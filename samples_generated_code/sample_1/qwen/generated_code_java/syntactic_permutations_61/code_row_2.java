public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        while (true) {
            byte[] buffer = new byte[bufferSize];
            buffer = null; // Free the buffer by dereferencing it
            System.gc();   // Suggest JVM to perform garbage collection
        }
    }
}