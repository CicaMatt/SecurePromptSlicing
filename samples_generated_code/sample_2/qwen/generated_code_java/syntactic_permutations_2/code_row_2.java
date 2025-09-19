import java.nio.BufferOverflowException;
import java.nio.ReadOnlyBufferException;

public class BufferCopy {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = 13;

        try {
            copyBytes(destination, source, numberOfBytesToCopy);
            System.out.println(new String(destination));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) throws BufferOverflowException, ReadOnlyBufferException {
        if (destination.length < numBytes) {
            throw new BufferOverflowException();
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}