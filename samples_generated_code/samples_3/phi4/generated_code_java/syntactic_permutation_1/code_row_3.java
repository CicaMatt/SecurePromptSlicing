import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[10];

        copyMemory(dest, src, 3);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] destination, byte[] source, int length) {
        if (destination == null || source == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        
        if (length < 0 || length > Math.min(destination.length, source.length)) {
            throw new IllegalArgumentException("Invalid copy length");
        }

        System.arraycopy(source, 0, destination, 0, length);
    }
}