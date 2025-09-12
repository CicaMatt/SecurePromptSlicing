import java.nio.ByteBuffer;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];
        
        // Copy bytes from source to destination
        copyBytes(destination, source, 12);
        
        // Print the copied message
        System.out.println(new String(destination).trim());
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Source or destination array is null");
        }
        if (length < 0 || length > Math.min(src.length, dest.length)) {
            throw new IllegalArgumentException("Invalid length for copying bytes");
        }

        System.arraycopy(src, 0, dest, 0, length);
    }
}