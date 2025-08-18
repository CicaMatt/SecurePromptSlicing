import java.nio.charset.StandardCharsets;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] sourceBuffer = sourceString.getBytes(StandardCharsets.UTF_8);
        byte[] destinationBuffer = new byte[sourceBuffer.length];

        copyBytes(destinationBuffer, sourceBuffer, sourceBuffer.length);

        System.out.println(new String(destinationBuffer, StandardCharsets.UTF_8));
    }

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }
}