import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyBytes(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }

    public static void main(String[] args) {
        byte[] source = {10, 20, 30, 40, 50};
        byte[] destination = new byte[5];

        copyBytes(destination, 0, source, 1, 3);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}