import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        // Example usage
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
        
        srcBuffer.limit(length).position(0);
        destBuffer.put(srcBuffer);
    }
}