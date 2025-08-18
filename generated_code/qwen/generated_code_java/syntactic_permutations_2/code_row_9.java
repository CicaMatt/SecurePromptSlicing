import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        int numberOfBytesToCopy = 3;
        
        copyBytes(destination, source, numberOfBytesToCopy);
        
        // For verification
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (length > source.length || length > destination.length) {
            throw new IllegalArgumentException("Length exceeds the size of source or destination array.");
        }
        
        System.arraycopy(source, 0, destination, 0, length);
    }
}