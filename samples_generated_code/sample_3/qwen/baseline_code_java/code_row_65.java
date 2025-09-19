import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceArray = sourceString.getBytes();
        byte[] destinationArray = new byte[sourceArray.length];

        copyBytes(destinationArray, sourceArray, sourceArray.length);

        System.out.println(new String(destinationArray));
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        if (numBytes > source.length || numBytes > destination.length) {
            throw new IllegalArgumentException("Number of bytes to copy exceeds the length of source or destination array.");
        }
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}