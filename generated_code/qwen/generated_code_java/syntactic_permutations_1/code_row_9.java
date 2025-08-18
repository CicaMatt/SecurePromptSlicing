import java.nio.BufferUnderflowException;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = {1, 2, 3, 4, 5};
        byte[] destination = new byte[5];
        int numberOfBytesToCopy = 3;

        copyBytes(destination, source, numberOfBytesToCopy);

        for (byte b : destination) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (length < 0) {
            throw new IllegalArgumentException("Length cannot be negative");
        }
        if (source.length < length) {
            throw new BufferUnderflowException();
        }
        if (destination.length < length) {
            throw new ArrayIndexOutOfBoundsException("Destination array is not large enough to hold the data.");
        }

        for (int i = 0; i < length; i++) {
            destination[i] = source[i];
        }
    }
}