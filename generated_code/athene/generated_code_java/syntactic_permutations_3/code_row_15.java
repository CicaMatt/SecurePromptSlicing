import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        String source = "Hello";
        byte[] dest = new byte[source.length()];
        
        copyMemory(dest, source.getBytes(), source.length());
        
        System.out.println(new String(dest));
    }

    public static void copyMemory(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}