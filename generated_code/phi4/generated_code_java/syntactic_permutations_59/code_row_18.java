import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        byte valueToFill = 'A';
        for (int i = 0; i < bufferSize; i++) {
            buffer.put(i, valueToFill);
        }

        System.out.println("Buffer filled with 'A': " + new String(buffer.array()));
    }
}