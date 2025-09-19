import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        // Copy bytes from source to destination
        copyBytes(destination, source, 5);

        // Print the contents of the destination array
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (src == null || dest == null || length < 0 || length > Math.min(src.length, dest.length)) {
            throw new IllegalArgumentException("Invalid arguments for memory copy.");
        }
        
        System.arraycopy(src, 0, dest, 0, length);
    }
}