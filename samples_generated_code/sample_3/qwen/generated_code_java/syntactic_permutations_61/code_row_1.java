import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        while (true) {
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate some processing with the buffer
            buffer.clear(); // Clear the buffer for reuse or free it manually in languages like C/C++
            
            // In Java, garbage collector will handle memory management,
            // so there's no explicit free operation needed.
            // However, setting the reference to null can help hint the GC.
            buffer = null;

            // Simulate some delay
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}