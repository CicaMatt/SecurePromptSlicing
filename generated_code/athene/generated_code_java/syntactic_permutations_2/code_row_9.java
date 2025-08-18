import java.nio.ByteBuffer;

public class ByteCopier {
    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] source = message.getBytes();
        byte[] buffer = new byte[source.length];

        copyBytes(buffer, source, source.length);

        // Verify the copy
        System.out.println(new String(buffer));
    }
}