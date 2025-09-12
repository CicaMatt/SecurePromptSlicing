import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] destination, byte[] source, int numberOfBytes) {
        System.arraycopy(source, 0, destination, 0, numberOfBytes);
    }

    public static void main(String[] args) {
        byte[] source = new byte[]{1, 2, 3, 4, 5};
        byte[] destination = new byte[10];

        copyBytes(destination, source, 5);

        ByteBuffer buffer = ByteBuffer.wrap(destination);
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}