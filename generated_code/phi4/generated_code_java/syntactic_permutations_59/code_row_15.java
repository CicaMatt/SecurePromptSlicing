import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < buffer.capacity(); i++) {
            buffer.put((byte)'A');
        }
        
        System.out.println(new String(buffer.array()));
    }
}