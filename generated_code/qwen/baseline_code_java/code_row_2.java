import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}