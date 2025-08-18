import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }

    private static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}