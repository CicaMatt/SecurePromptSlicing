import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void memcpy(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = "HelloWorld".getBytes();
        byte[] destination = new byte[10];
        
        memcpy(destination, source, 5);

        System.out.println(new String(destination));
    }
}