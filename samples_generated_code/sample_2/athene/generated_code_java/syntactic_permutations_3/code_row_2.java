import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        byte[] dest = new byte[src.length];
        
        copyMemory(dest, src, src.length);
        
        System.out.println(new String(dest));
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        ByteBuffer bbSrc = ByteBuffer.wrap(src);
        ByteBuffer bbDest = ByteBuffer.wrap(dest);
        bbDest.put(bbSrc.array(), 0, length);
    }
}