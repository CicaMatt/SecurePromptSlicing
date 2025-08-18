import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, numBytes));
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[20];
        
        copyBytes(buffer, message, message.length);
        
        System.out.println(new String(buffer).trim());
    }
}