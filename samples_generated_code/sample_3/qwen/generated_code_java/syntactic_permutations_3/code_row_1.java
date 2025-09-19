import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        ByteBuffer destinationBuffer = ByteBuffer.allocate(sourceBytes.length);

        copyMemory(destinationBuffer.array(), 0, sourceBytes, 0, sourceBytes.length);

        System.out.println(new String(destinationBuffer.array()));
    }

    public static void copyMemory(byte[] dest, int destOffset, byte[] src, int srcOffset, int length) {
        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }
}