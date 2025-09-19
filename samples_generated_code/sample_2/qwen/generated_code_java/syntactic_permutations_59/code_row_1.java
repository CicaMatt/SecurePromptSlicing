import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) 'A');
        }

        buffer.rewind(); // Reset position to the start of the buffer for reading if needed

        // For demonstration, print out the first 10 bytes
        for (int i = 0; i < 10; i++) {
            System.out.print((char) buffer.get());
        }
    }
}