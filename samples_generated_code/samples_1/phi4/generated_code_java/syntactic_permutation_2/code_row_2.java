import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, world!".getBytes(StandardCharsets.UTF_8);
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, source, source.length);

        String result = new String(destination.array(), StandardCharsets.UTF_8).trim();
        System.out.println(result);
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numBytes) {
        if (destination.remaining() < numBytes || source.length < numBytes) {
            throw new IllegalArgumentException("Destination buffer or source array is too small.");
        }
        destination.put(source, 0, numBytes);
    }
}