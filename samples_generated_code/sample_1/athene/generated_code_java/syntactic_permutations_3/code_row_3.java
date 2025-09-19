import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(new String(destination));
    }
}