import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];

        // Copy 5 bytes from source to destination starting at offset 0 in both arrays.
        copyBytes(destination, 0, source, 0, 5);

        String result = new String(destination).trim();
        System.out.println("Copied message: " + result);
    }

    public static void copyBytes(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        if (dest == null || src == null || dest.length < destPos + length || src.length < srcPos + length) {
            throw new IllegalArgumentException("Invalid positions or lengths for copying.");
        }
        
        System.arraycopy(src, srcPos, dest, destPos, length);
    }
}