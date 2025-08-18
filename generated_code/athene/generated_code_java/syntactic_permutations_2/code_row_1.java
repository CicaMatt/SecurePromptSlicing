import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[message.length];
        
        copyMemory(buffer, message, message.length);
        
        System.out.println(new String(buffer));
    }
}