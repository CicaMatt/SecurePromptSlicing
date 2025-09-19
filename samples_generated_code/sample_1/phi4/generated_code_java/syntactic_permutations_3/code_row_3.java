import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] destination = new byte[10];
        String text = "Hello";
        
        copyBytes(destination, text.getBytes(), text.length());
        
        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length < 0 || length > src.length || length > dest.length) {
            throw new IllegalArgumentException("Invalid arguments for copying bytes");
        }
        
        System.arraycopy(src, 0, dest, 0, length);
    }
}