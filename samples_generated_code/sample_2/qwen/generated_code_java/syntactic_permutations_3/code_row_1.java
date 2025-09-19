import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] destinationBuffer = new byte[sourceString.getBytes().length];

        copyBytes(destinationBuffer, sourceString.getBytes(), sourceString.getBytes().length);

        System.out.println(new String(destinationBuffer));
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        if (destination.length < length || source.length < length) {
            throw new IllegalArgumentException("Destination or source buffer is not large enough.");
        }
        System.arraycopy(source, 0, destination, 0, length);
    }
}