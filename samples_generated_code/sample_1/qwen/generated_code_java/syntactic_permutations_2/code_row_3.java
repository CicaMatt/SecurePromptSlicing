import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {0x1, 0x2, 0x3, 0x4, 0x5};
        byte[] destination = new byte[source.length];
        int numBytesToCopy = source.length;

        copyMemory(destination, source, numBytesToCopy);

        for (byte b : destination) {
            System.out.printf("%02X ", b);
        }
    }

    public static void copyMemory(byte[] dst, byte[] src, int bytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dst, 0, bytes);
    }
}