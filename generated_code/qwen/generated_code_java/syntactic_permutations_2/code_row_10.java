import java.nio.BufferOverflowException;

public class BufferCopier {
    public static void main(String[] args) {
        byte[] source = { 1, 2, 3, 4, 5 };
        byte[] destination = new byte[5];
        int numberOfBytesToCopy = 3;
        
        try {
            copyBytes(destination, source, numberOfBytesToCopy);
            System.out.println(java.util.Arrays.toString(destination));
        } catch (BufferOverflowException e) {
            System.err.println("Error: Not enough space in the destination buffer.");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) throws BufferOverflowException {
        if (destination.length < length) {
            throw new BufferOverflowException();
        }
        System.arraycopy(source, 0, destination, 0, length);
    }
}