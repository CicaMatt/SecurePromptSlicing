import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, source, source.length);

        destination.flip();
        System.out.println(new String(destination.array()));
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        if (numBytes > src.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of the source array.");
        }
        dest.put(src, 0, numBytes);
    }
}