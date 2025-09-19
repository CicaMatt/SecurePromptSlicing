import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        int numBytesToCopy = 5;
        byte[] destination = new byte[source.length];

        copyMemory(destination, source, numBytesToCopy);

        System.out.println(new String(destination).trim());
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes <= 0) return;
        
        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}