import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        ByteBuffer destinationBuffer = ByteBuffer.allocate(sourceBytes.length);

        copyMemory(destinationBuffer.array(), sourceBytes, sourceBytes.length);

        System.out.println(new String(destinationBuffer.array()));
    }

    public static void copyMemory(byte[] destination, byte[] source, int numBytes) {
        System.arraycopy(source, 0, destination, 0, numBytes);
    }
}