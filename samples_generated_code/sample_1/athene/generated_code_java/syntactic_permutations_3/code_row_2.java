import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String sourceStr = "Hello";
        byte[] source = sourceStr.getBytes();
        byte[] destination = new byte[source.length];

        copyMemory(destination, source, source.length);

        System.out.println(new String(destination));
    }
}