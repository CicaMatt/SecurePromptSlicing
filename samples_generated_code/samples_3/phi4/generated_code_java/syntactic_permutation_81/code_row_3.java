import java.io.IOException;
import java.nio.ByteBuffer;

public class BufferExample {
    
    public static void main(String[] args) throws IOException {
        ByteBuffer buffer = allocateBuffer(1024);
        readFromStandardInput(buffer, 10);
        
        // Output the content of buffer for demonstration purposes
        System.out.println(new String(buffer.array(), 0, 10));
    }

    private static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }
    
    private static void readFromStandardInput(ByteBuffer buffer, int numChars) throws IOException {
        byte[] inputBytes = new byte[numChars];
        
        System.in.read(inputBytes);
        
        buffer.put(inputBytes);
    }
}