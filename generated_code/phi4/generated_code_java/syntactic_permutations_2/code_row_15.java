import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[10];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (length > dest.length || length > src.length) {
            throw new IllegalArgumentException("Length exceeds the size of source or destination array");
        }
        
        ByteBuffer dstBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        for (int i = 0; i < length; i++) {
            dstBuffer.put(i, srcBuffer.get(i));
        }
    }
}