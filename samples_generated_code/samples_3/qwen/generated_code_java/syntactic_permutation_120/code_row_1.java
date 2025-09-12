import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);
        
        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('a' + i));
        }
        
        // Reset the position of buffer1 to the beginning before copying
        buffer1.rewind();
        
        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);
        
        // Reset the position of buffer2 to the beginning before reading
        buffer2.rewind();
        
        // Print the contents of buffer2
        for (int i = 0; i < size; i++) {
            System.out.print((char) buffer2.get());
        }
    }
}