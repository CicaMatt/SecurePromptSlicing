import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }

    public static void main(String[] args) {
        String message = "Hello";
        ByteBuffer buffer = ByteBuffer.allocate(5);
        
        for (int i = 0; i < message.length(); i++) {
            buffer.put((byte) message.charAt(i));
        }
        
        byte[] destBuffer = new byte[buffer.capacity()];
        copyBytes(destBuffer, buffer.array(), buffer.position());
        
        String result = new String(destBuffer).trim();
        System.out.println(result);
    }
}