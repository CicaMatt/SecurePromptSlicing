import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBytes = sourceString.getBytes();
        byte[] destinationBuffer = new byte[sourceBytes.length];

        copyMemory(sourceBytes, 0, destinationBuffer, 0, sourceBytes.length);

        System.out.println(new String(destinationBuffer));
    }

    public static void copyMemory(byte[] src, int srcOffset, byte[] dest, int destOffset, int length) {
        System.arraycopy(src, srcOffset, dest, destOffset, length);
    }
}