import java.nio.BufferUnderflowException;
import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void copyMemory(byte[] destination, byte[] source, int numBytes) {
        if (numBytes < 0 || numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Invalid number of bytes to copy");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[source.length];

        int bytesToCopy = 3;
        copyMemory(destination, source, bytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }
}