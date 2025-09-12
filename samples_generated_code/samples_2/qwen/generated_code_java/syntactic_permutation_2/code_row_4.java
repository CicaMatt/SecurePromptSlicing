import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, source, source.length);

        // Reset position to read from the beginning
        destination.flip();

        byte[] result = new byte[destination.remaining()];
        destination.get(result);
        System.out.println(new String(result));
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        if (numBytes > src.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source array length.");
        }
        if (dest.remaining() < numBytes) {
            throw new IllegalArgumentException("Destination buffer does not have enough space.");
        }

        dest.put(src, 0, numBytes);
    }
}