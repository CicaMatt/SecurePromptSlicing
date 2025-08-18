import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        ByteBuffer destinationBuffer = ByteBuffer.allocate(sourceBytes.length);

        copyMemory(destinationBuffer.array(), sourceBytes, sourceBytes.length);

        System.out.println(new String(destinationBuffer.array()));
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}