import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] source = sourceString.getBytes();
        byte[] destination = new byte[source.length];

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination));
    }
}