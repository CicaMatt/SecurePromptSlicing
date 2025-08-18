import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 3;
        
        copyMemory(destination, source, numberOfBytesToCopy);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, numBytes);
    }
}