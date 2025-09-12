import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];

        copyBytes(destination, source, 13);

        System.out.println(new String(destination).trim());
    }

    private static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        for (int i = 0; i < numBytes && i < src.length; i++) {
            destBuffer.put(i, srcBuffer.get(i));
        }
    }
}