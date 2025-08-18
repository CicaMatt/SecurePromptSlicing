import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];

        copyMemory(destination, 0, source, 0, source.length);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }
}