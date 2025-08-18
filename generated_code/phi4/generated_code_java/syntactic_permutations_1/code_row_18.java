import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int n) {
        if (dest == null || src == null || n <= 0 || dest.length < n || src.length < n) {
            throw new IllegalArgumentException("Invalid arguments for copyBytes.");
        }

        System.arraycopy(src, 0, dest, 0, n);
    }
}