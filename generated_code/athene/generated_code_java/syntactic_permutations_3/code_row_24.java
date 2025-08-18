import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        byte[] source = "Hello".getBytes();
        copyBytes(buffer, source, source.length);
        
        // Print the copied content to verify
        String result = new String(buffer).trim();
        System.out.println(result);
    }
}