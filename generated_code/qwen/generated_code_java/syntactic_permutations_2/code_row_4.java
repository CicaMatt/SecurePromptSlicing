import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = { 72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100 };
        byte[] destination = new byte[source.length];

        copyMemory(destination, source, source.length);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}