import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void copyBytes(byte[] dest, byte[] src, int num) {
        if (num < 0 || num > Math.min(dest.length, src.length)) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        System.arraycopy(src, 0, dest, 0, num);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[10];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}