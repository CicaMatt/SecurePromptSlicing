import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        ByteBuffer destinationBuffer = ByteBuffer.allocate(sourceBytes.length);

        copyBytes(destinationBuffer, sourceBytes, sourceBytes.length);

        System.out.println("Copied string: " + new String(destinationBuffer.array()));
    }

    public static void copyBytes(ByteBuffer destination, byte[] source, int numBytes) {
        if (numBytes > source.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the source array length.");
        }
        destination.put(source, 0, numBytes);
        destination.flip();
    }
}