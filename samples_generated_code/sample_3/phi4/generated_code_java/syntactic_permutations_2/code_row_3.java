import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = { 'H', 'e', 'l', 'l', 'o' };
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest.length < length || src.length < length) {
            throw new IllegalArgumentException("Source or destination array is too small.");
        }
        
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        for (int i = 0; i < length; i++) {
            destBuffer.put(i, srcBuffer.get(i));
        }
    }
}