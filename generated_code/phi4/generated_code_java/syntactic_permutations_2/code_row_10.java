import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        // Example usage
        byte[] destination = new byte[10];
        byte[] source = {1, 2, 3, 4, 5};
        int numBytesToCopy = 5;
        
        copyBytes(destination, source, numBytesToCopy);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytesToCopy) {
        if (destination == null || source == null || numBytesToCopy <= 0) return;
        
        int bytesToCopy = Math.min(numBytesToCopy, destination.length);
        bytesToCopy = Math.min(bytesToCopy, source.length);

        System.arraycopy(source, 0, destination, 0, bytesToCopy);
    }
}