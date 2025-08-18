import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBuffer = sourceString.getBytes();
        byte[] destinationBuffer = new byte[sourceBuffer.length];

        copyBytes(destinationBuffer, sourceBuffer, sourceBuffer.length);

        System.out.println(new String(destinationBuffer));
    }
}