import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest.length < length || src.length < length) {
            throw new IllegalArgumentException("Source or Destination array too short");
        }

        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        for (int i = 0; i < length; i++) {
            byte data = srcBuffer.get(i);
            destBuffer.put(i, data);
        }
    }
}