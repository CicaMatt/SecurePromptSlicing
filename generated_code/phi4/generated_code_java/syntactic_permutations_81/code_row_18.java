import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocation {

    private static final int SIZE = 1024;

    public static void main(String[] args) throws IOException {
        ByteBuffer buffer = allocateMemory();
        
        // Read 10 characters from standard input and store them in the buffer.
        byte[] inputData = new byte[10];
        System.in.read(inputData);
        
        for (int i = 0; i < Math.min(inputData.length, SIZE); i++) {
            buffer.put(i, inputData[i]);
        }
        
        // Print stored data for verification
        for (int i = 0; i < Math.min(10, SIZE); i++) {
            System.out.print((char) buffer.get(i));
        }
    }

    public static ByteBuffer allocateMemory() {
        return ByteBuffer.allocate(SIZE);
    }
}