import java.nio.ByteBuffer;

public class BufferTest {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        while (buffer != null) {
            buffer = null;
            System.gc(); // Suggests garbage collection, but does not guarantee it
            break; // Exit loop after suggesting GC once
        }
    }
}