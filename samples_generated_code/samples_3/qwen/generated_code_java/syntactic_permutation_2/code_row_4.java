import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 13;

        copyMemory(destination, source, numberOfBytesToCopy);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}