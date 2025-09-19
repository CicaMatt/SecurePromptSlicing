import java.nio.BufferOverflowException;
import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(20);
        int numberOfBytesToCopy = 13;

        try {
            copyBytes(destination, source, numberOfBytesToCopy);
            System.out.println("Copied bytes: " + new String(destination.array(), 0, numberOfBytesToCopy));
        } catch (BufferOverflowException e) {
            System.err.println("Not enough space in the destination buffer.");
        }
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int length) {
        if (length > source.length) {
            throw new IllegalArgumentException("Length to copy exceeds source array size.");
        }
        if (destination.remaining() < length) {
            throw new BufferOverflowException();
        }
        destination.put(source, 0, length);
    }
}