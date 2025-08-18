import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        int numberOfBytesToCopy = 3;
        
        copyMemory(destination, source, numberOfBytesToCopy);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        if (length < 0 || src.length - length < 0 || dest.length - length < 0) {
            throw new IndexOutOfBoundsException("Length is negative or exceeds array bounds");
        }
        
        ByteBuffer buffer = ByteBuffer.wrap(src);
        buffer.get(dest, 0, length);
    }
}