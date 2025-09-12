import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, Math.min(length, src.length));
    }

    public static void main(String[] args) {
        String str = "Hello";
        byte[] buffer = new byte[10];
        
        copyBytes(buffer, str.getBytes(), str.length());
        
        for (byte b : buffer) {
            System.out.print((char) b);
        }
    }
}