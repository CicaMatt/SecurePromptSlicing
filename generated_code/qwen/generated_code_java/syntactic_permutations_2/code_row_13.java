import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 5;

        copyMemory(destination, source, numberOfBytesToCopy);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}