import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(byte[] destination, byte[] source, int numBytes) {
        if (source.length < numBytes || destination.length < numBytes) {
            throw new IllegalArgumentException("Source or Destination array is not large enough.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        
        copyMemory(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}