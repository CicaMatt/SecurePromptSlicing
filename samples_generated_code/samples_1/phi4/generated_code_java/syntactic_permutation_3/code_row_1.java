import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[5];
        
        copyBytes(destination, 0, source, 0, 5);
        
        String result = new String(destination);
        System.out.println(result); // Should print: Hello
    }

    public static void copyBytes(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        if (dest.length < destPos + length || src.length < srcPos + length) {
            throw new IllegalArgumentException("Invalid positions or lengths for the arrays.");
        }
        
        System.arraycopy(src, srcPos, dest, destPos, length);
    }
}