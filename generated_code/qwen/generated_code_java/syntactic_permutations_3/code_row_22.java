import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String source = "Hello";
        ByteBuffer destination = ByteBuffer.allocate(source.getBytes(StandardCharsets.UTF_8).length);
        byte[] sourceBytes = source.getBytes(StandardCharsets.UTF_8);

        copyMemory(destination, sourceBytes, source.length());

        // Convert ByteBuffer back to String for verification
        byte[] destArray = new byte[source.length()];
        destination.flip();
        destination.get(destArray);
        String result = new String(destArray, StandardCharsets.UTF_8);
        System.out.println(result);
    }

    public static void copyMemory(ByteBuffer destination, byte[] source, int num) {
        if (num > source.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of the source array.");
        }
        destination.put(source, 0, num);
    }
}