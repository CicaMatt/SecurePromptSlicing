import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 3;
        
        copyMemory(destination, source, numberOfBytesToCopy);
        
        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] destination, byte[] source, int length) {
        if (length < 0 || length > source.length || length > destination.length) {
            throw new IllegalArgumentException("Invalid length");
        }
        
        ByteBuffer buffer = ByteBuffer.wrap(source);
        buffer.get(destination, 0, length);
    }
}