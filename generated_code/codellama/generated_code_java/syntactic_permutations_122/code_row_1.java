import java.nio.ByteBuffer;

public class Memory {
    public static void main(String[] args) {
        // Allocate memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Copy contents from buffer1 to buffer2
        for (int i = 0; i < 10; i++) {
            byte b = buffer1.get(i);
            buffer2.put(b);
        }

        // Free memory of buffer1
        buffer1.clear();

        // Free memory of buffer2
        buffer2.clear();
    }
}