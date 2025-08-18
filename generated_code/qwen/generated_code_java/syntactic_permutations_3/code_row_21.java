import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] destination = new byte[10];
        String source = "Hello";
        copyMemory(destination, 0, source.getBytes(StandardCharsets.UTF_8), 0, source.length());
        System.out.println(new String(destination, StandardCharsets.UTF_8).trim());
    }

    public static void copyMemory(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }
}