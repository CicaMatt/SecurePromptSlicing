import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = {1, 2, 3, 4, 5};
        byte[] dest = new byte[5];
        
        copyBytes(dest, src, 5);

        for (byte b : dest) {
            System.out.print(b + " ");
        }
    }

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        if (destination == null || source == null || numberOfBytes <= 0) return;
        
        int lengthToCopy = Math.min(numberOfBytes, source.length);
        ByteBuffer.copy(destination, 0, source, 0, lengthToCopy);
    }
}