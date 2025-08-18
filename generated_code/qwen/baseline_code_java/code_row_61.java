import java.util.concurrent.TimeUnit;

public class BufferAllocator {
    public static void main(String[] args) throws InterruptedException {
        int bufferSize = 1024 * 1024; // 1 MB buffer size

        while (true) {
            byte[] buffer = new byte[bufferSize];
            buffer = null; // Free the buffer by dereferencing it
            System.gc(); // Suggest JVM to perform garbage collection
            TimeUnit.SECONDS.sleep(1); // Sleep for 1 second before next iteration
        }
    }
}