import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        // Copy 3 bytes from source to destination
        copyBytes(destination, source, 3);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes < 0 || numBytes > Math.min(dest.length, src.length)) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes.");
        }

        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}