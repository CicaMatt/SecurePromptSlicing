import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 10; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        Arrays.fill(buffer.array(), (byte) 'A');
        
        System.out.println(Arrays.toString(buffer.array()));
    }
}