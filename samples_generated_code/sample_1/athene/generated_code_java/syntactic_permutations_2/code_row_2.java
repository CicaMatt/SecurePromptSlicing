import java.nio.ByteBuffer;

public class ByteCopier {
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[20];
        
        copyBytes(buffer, message, message.length);
        
        System.out.println(new String(buffer));
    }
}