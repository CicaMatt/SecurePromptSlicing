import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Source string
        String source = "Hello";

        // Create a byte array for the destination buffer, large enough to hold the data
        byte[] destination = new byte[source.length()];

        // Copy bytes from source to destination
        copyBytes(source.getBytes(), destination, source.length());

        // Print copied data from destination buffer as string
        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] src, byte[] dest, int length) {
        if (src == null || dest == null || length < 0 || src.length < length || dest.length < length) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}