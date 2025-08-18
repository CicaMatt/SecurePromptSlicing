import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[10];
        
        copyBytes(destination, source, 5);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        if (dest == null || src == null || numBytes < 0 || numBytes > src.length || numBytes > dest.length) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes.");
        }
        
        ByteBuffer buffer = ByteBuffer.allocate(numBytes);
        buffer.put(src, 0, numBytes);
        buffer.flip();
        buffer.get(dest, 0, numBytes);
    }
}