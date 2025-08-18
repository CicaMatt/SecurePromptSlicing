import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        
        // Buffer for destination, with enough size (same as source)
        ByteBuffer destBuffer = ByteBuffer.allocate(src.length);

        copyBytes(destBuffer, src, src.length);
        
        String result = new String(destBuffer.array()).trim();
        System.out.println(result);
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numberOfBytes) {
        destination.put(source, 0, numberOfBytes);
    }
}