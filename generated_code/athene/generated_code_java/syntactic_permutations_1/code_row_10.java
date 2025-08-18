import java.nio.ByteBuffer;

public class ByteCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        copyBytes(destination, source, 3);
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}