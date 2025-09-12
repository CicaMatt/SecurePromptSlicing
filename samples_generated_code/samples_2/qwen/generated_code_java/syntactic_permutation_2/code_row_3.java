import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];

        copyMemory(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}