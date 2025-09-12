import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int numberOfBytesToCopy = 5;
        
        ByteBuffer buffer = ByteBuffer.allocate(source.length);
        copyMemory(buffer.array(), source, numberOfBytesToCopy);
        
        System.out.println(java.util.Arrays.toString(buffer.array()));
    }

    public static void copyMemory(byte[] destination, byte[] source, int length) {
        System.arraycopy(source, 0, destination, 0, length);
    }
}