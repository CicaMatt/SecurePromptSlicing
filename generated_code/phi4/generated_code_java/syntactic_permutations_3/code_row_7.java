import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Create a buffer with enough space for "Hello"
        ByteBuffer destination = ByteBuffer.allocate(5);

        // Copy "Hello" to the destination buffer
        copyBytes(destination, "Hello".getBytes(), 5);

        // Convert back to string and print
        System.out.println(new String(destination.array()).trim());
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest.put(i, src[i]);
        }
    }
}