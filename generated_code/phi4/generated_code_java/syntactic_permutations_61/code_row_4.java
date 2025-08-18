public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        // Allocate buffer
        byte[] buffer = new byte[bufferSize];

        // Simulate freeing the buffer in a loop (in Java, this is done by letting it go out of scope)
        for (int i = 0; i < 5; i++) {
            buffer = null;
            System.gc(); // Suggest garbage collection
        }
    }
}