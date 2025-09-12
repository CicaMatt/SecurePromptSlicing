import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Additional operations on the buffer can be added here

        System.out.println("Buffer allocated with size: " + buffer.capacity());
    }
}