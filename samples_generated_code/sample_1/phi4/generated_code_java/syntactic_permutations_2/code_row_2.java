import java.nio.ByteBuffer;

public class ByteCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        if (destination == null || source == null || numberOfBytes < 0 || numberOfBytes > source.length) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        ByteBuffer destBuffer = ByteBuffer.wrap(destination);
        ByteBuffer srcBuffer = ByteBuffer.wrap(source);

        destBuffer.put(srcBuffer.limit(numberOfBytes));
    }

    public static void main(String[] args) {
        byte[] destination = new byte[10];
        byte[] source = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        
        copyBytes(destination, source, 5);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}