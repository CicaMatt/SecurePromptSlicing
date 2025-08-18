import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, numBytes));
    }

    public static void main(String[] args) {
        byte[] source = "HelloWorld".getBytes();
        byte[] destination = new byte[10];
        copyBytes(destination, source, 5);
        System.out.println(new String(destination));
    }
}