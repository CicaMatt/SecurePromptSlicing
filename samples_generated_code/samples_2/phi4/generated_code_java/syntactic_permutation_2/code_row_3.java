import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[20];

        copyMemory(destination, source, 13);

        System.out.println(new String(destination).trim());
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes < 0 || numBytes > Math.min(dest.length, src.length)) {
            throw new IllegalArgumentException("Invalid arguments for memory copy.");
        }
        
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}