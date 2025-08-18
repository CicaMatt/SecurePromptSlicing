import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];

        copyBytes(destination, 0, source, 0, source.length);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        for (int i = 0; i < length; i++) {
            dest[destPos + i] = src[srcPos + i];
        }
    }
}