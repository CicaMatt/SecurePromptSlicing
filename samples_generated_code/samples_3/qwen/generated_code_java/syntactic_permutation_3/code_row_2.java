import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceArray = sourceString.getBytes();
        ByteBuffer destinationBuffer = ByteBuffer.allocate(sourceArray.length);

        copyBytes(destinationBuffer.array(), sourceArray, sourceArray.length);

        System.out.println(new String(destinationBuffer.array()));
    }

    public static void copyBytes(byte[] destination, byte[] source, int numBytes) {
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}