import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = { 72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100 }; // "Hello World"
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = source.length;

        copyMemory(destination, source, numberOfBytesToCopy);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}