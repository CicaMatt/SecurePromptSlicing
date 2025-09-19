import java.nio.ByteBuffer;

public class ByteCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer dstBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);
        for (int i = 0; i < numBytes; i++) {
            dstBuffer.put(i, srcBuffer.get(i));
        }
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[20];
        copyBytes(buffer, message, message.length);
        System.out.println(new String(buffer).trim());
    }
}