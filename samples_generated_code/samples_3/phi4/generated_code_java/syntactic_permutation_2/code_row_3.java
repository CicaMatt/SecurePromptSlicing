import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20]; // Ensure it's large enough to hold the copied data

        copyBytes(destination, source, 13); // Copy first 13 bytes as an example
        System.out.println(new String(destination, 0, 13)); // Print only the copied part
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (src == null || dest == null) {
            throw new IllegalArgumentException("Source and destination cannot be null");
        }
        if (length < 0 || length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Invalid length for copying");
        }

        System.arraycopy(src, 0, dest, 0, length);
    }
}