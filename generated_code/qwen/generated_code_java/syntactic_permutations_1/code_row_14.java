import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (destination == null || source == null) {
            throw new NullPointerException("Source and destination arrays must not be null");
        }
        if (numBytes < 0) {
            throw new IllegalArgumentException("Number of bytes to copy must be non-negative");
        }
        if (source.length < numBytes) {
            throw new BufferUnderflowException();
        }
        if (destination.length < numBytes) {
            throw new BufferOverflowException();
        }

        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];

        copyBytes(destination, source, 5);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}