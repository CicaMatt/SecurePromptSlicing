import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        byte[] dest = new byte[src.length];
        
        memoryCopy(dest, src, src.length);
        
        System.out.println(new String(dest));
    }

    public static void memoryCopy(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(src).get(dest, 0, numBytes);
    }
}