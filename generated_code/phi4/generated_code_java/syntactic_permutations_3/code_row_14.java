import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes(StandardCharsets.UTF_8);
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, source, source.length);

        System.out.println(new String(destination.array(), StandardCharsets.UTF_8));
    }

    private static void copyBytes(ByteBuffer dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest.put(src[i]);
        }
    }
}