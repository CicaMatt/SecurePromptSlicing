import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes(StandardCharsets.UTF_8);
        byte[] destination = new byte[20];

        copyMemory(destination, 0, source, 0, source.length);

        System.out.println(new String(destination, 0, source.length, StandardCharsets.UTF_8));
    }

    public static void copyMemory(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        if (length < 0 || destPos + length > dest.length || srcPos + length > src.length) {
            throw new IllegalArgumentException("Invalid arguments for memory copy");
        }
        
        System.arraycopy(src, srcPos, dest, destPos, length);
    }
}