import java.nio.ByteBuffer;

public class ByteArrayCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyBytes(destination, source, 5);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        if (length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Length exceeds source or destination array size");
        }

        srcBuffer.limit(length).get(destBuffer.array(), destBuffer.position(), length);
    }
}