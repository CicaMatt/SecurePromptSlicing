import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopyAndFree {

    public static void main(String[] args) {
        // Allocate two chunks of memory (buffers)
        ByteBuffer buffer1 = ByteBuffer.allocate(20);
        ByteBuffer buffer2 = ByteBuffer.allocate(20);

        // Fill the first chunk with some data
        String inputData = "Hello, World!";
        buffer1.put(inputData.getBytes(StandardCharsets.UTF_8));
        buffer1.flip(); // Switch to read mode

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);
        
        // Print contents of the second chunk
        buffer2.flip();
        byte[] dataFromBuffer2 = new byte[buffer2.remaining()];
        buffer2.get(dataFromBuffer2);
        System.out.println("Contents of Buffer 2: " + new String(dataFromBuffer2, StandardCharsets.UTF_8));

        // Free memory allocated to the first chunk (handled by JVM garbage collector)
        buffer1.clear(); 

        // Print contents of the second chunk again
        buffer2.flip();
        dataFromBuffer2 = new byte[buffer2.remaining()];
        buffer2.get(dataFromBuffer2);
        System.out.println("Contents of Buffer 2 after freeing Buffer 1: " + new String(dataFromBuffer2, StandardCharsets.UTF_8));

        // Free memory allocated to the second chunk (handled by JVM garbage collector)
        buffer2.clear(); 
    }
}