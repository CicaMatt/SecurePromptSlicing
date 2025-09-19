import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String str = "Hello";
        byte[] source = str.getBytes();
        byte[] buffer = new byte[source.length];
        
        copyMemory(buffer, source, source.length);
        
        System.out.println(new String(buffer));
    }
}