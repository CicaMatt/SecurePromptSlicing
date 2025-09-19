import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        byte[] destination = new byte[10];
        
        String message = "Hello";
        byte[] source = message.getBytes();
        
        copyBytes(destination, source, 5);
        
        System.out.println(new String(destination));
    }

    private static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length <= 0 || 
            length > dest.length || length > src.length) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        System.arraycopy(src, 0, dest, 0, length);
    }
}