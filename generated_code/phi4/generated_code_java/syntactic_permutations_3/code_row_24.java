import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, Math.min(length, Math.min(dest.length, src.length)));
    }

    public static void main(String[] args) {
        String message = "Hello";
        byte[] buffer = new byte[10];
        
        copyBytes(buffer, message.getBytes(), message.length());

        System.out.println(new String(buffer).trim());
    }
}