import java.nio.ByteBuffer;

public class Main {
    public static void main(String[] args) {
        // Create two buffers with 10 bytes each
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);
        
        // Write some data into the first buffer
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte)(i * 3));
        }
        
        // Copy the data from the first buffer to the second one
        buffer2.put(buffer1);
        
        // Print the contents of the second buffer
        for (int i = 0; i < buffer2.capacity(); i++) {
            System.out.println(buffer2.get(i));
        }
    }
}