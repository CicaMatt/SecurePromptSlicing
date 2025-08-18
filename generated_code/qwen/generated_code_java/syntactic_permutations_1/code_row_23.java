import java.nio.BufferUnderflowException;
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

    public static void copyMemory(byte[] dest, byte[] src, int num) {
        if (num > src.length || num > dest.length) {
            throw new BufferUnderflowException();
        }
        System.arraycopy(src, 0, dest, 0, num);
    }
}