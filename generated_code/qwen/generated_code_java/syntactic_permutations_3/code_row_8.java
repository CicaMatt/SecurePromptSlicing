import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer destination = ByteBuffer.allocate(10);
        String source = "Hello";
        
        copyStringToByteBuffer(destination, source);
        
        // Reset position and print to verify content
        destination.position(0);
        System.out.println(new String(destination.array(), 0, source.length()));
    }

    public static void copyStringToByteBuffer(ByteBuffer destination, String source) {
        byte[] bytes = source.getBytes();
        if (bytes.length <= destination.remaining()) {
            destination.put(bytes);
        } else {
            throw new IllegalArgumentException("Source string is too large for the destination buffer.");
        }
    }
}