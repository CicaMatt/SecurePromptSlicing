import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        int numberOfBytesToCopy = source.length;

        copyMemory(destination, source, numberOfBytesToCopy);

        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] destination, byte[] source, int numberOfBytesToCopy) {
        ByteBuffer buffer = ByteBuffer.wrap(source);
        buffer.get(destination, 0, numberOfBytesToCopy);
    }
}