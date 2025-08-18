import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }

    public static void main(String[] args) {
        // Example usage:
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[10]; // Larger size to hold the copied data

        copyMemory(destination, source, source.length);

        // Print out the contents of the destination array
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}