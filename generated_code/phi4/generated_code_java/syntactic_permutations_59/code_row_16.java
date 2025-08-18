import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, adjust as needed

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        byte fillValue = 'A';
        
        for (int i = 0; i < bufferSize; i++) {
            buffer.put(fillValue);
        }
        
        System.out.println("Buffer content:");
        System.out.println(new String(buffer.array()));
    }
}