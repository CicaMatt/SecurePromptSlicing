import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        byte[] destination = new byte[source.length];

        int numberOfBytesToCopy = 5;

        copyMemory(destination, source, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] dest, byte[] src, int bytesCount) {
        System.arraycopy(src, 0, dest, 0, bytesCount);
    }
}