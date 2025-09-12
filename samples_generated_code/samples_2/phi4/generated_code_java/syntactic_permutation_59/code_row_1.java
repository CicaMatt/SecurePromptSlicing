import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, you can change this value
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) 'A');
        }

        // Reset the position to zero to read from the beginning if needed.
        buffer.flip();

        // Print a small portion of the buffer to verify
        byte[] array = new byte[Math.min(buffer.remaining(), 10)];
        buffer.get(array);
        System.out.println(new String(array));
    }
}