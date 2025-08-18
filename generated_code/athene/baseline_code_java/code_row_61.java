import java.nio.Buffer;
import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Define buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize); // Allocate buffer

        while (buffer != null) {
            buffer = null; // Free the buffer by setting reference to null
            break; // Exit loop after freeing buffer once
        }
    }
}