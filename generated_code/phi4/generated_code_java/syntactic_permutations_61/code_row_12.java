import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, modify as needed

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Example usage of the buffer (optional)
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) i);
        }

        // Reset position to read from the beginning
        buffer.flip();

        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}