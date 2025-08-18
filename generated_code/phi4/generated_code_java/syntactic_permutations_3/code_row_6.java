import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10]; // Ensure enough space for copying

        copyMemory(destination, source, source.length);

        System.out.println(new String(destination).trim());
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes < 0) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}