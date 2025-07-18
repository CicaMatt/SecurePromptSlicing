import java.nio.ByteBuffer;

public class Solution {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);
        
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
            buffer2.put((byte) 9 - i);
        }
        
        for (int i = 0; i < 10; i++) {
            System.out.println(buffer1.get());
        }
        buffer1.flip();
        buffer2.rewind();
        while (buffer1.hasRemaining() && buffer2.hasRemaining()) {
            byte b = buffer1.get();
            buffer2.put(b);
        }
        
        for (int i = 0; i < 10; i++) {
            System.out.println(buffer2.get());
        }
    }
}