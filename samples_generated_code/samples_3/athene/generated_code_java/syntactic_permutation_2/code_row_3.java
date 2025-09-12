import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] buffer = new byte[message.length()];
        byte[] messageBytes = message.getBytes();

        copyBytes(buffer, messageBytes, messageBytes.length);

        System.out.println(new String(buffer));
    }
}