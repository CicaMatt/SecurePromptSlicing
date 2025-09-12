import java.util.Random;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        byte[] buffer = new byte[bufferSize];

        Random random = new Random();
        for (int i = 0; i < 10; i++) { // Example loop to "free" the buffer
            buffer = null;
            System.gc(); // Suggesting JVM to perform garbage collection
            try {
                Thread.sleep(random.nextInt(100)); // Simulate some work and delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            buffer = new byte[bufferSize]; // Reallocate the buffer
        }
    }
}