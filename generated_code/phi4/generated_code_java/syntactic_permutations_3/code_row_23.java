import java.nio.ByteBuffer;

public class ByteCopier {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String message = "Hello";
        byte[] sourceBuffer = message.getBytes();
        byte[] destinationBuffer = new byte[10]; // Adjust size as needed

        copyBytes(destinationBuffer, sourceBuffer, sourceBuffer.length);

        System.out.println(new String(destinationBuffer).trim());
    }
}