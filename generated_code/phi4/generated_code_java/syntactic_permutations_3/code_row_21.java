import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] destination = new byte[10];
        String sourceString = "Hello";
        
        copyBytes(destination, sourceString.getBytes(StandardCharsets.UTF_8), 5);
        
        System.out.println(new String(destination, StandardCharsets.UTF_8).trim());
    }

    public static void copyBytes(byte[] destination, byte[] source, int num) {
        ByteBuffer destBuffer = ByteBuffer.wrap(destination);
        ByteBuffer srcBuffer = ByteBuffer.wrap(source);

        for (int i = 0; i < num && i < srcBuffer.remaining(); i++) {
            destBuffer.put(srcBuffer.get());
        }
    }
}