import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = {0x1, 0x2, 0x3, 0x4, 0x5};
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 3;

        copyMemory(destination, source, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.printf("%02X ", b);
        }
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}