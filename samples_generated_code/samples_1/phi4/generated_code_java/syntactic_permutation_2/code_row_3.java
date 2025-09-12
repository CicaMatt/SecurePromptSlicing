import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        int numBytesToCopy = 3;
        byte[] dest = new byte[5];

        copyMemory(dest, src, numBytesToCopy);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyMemory(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds source or destination length.");
        }
        
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}