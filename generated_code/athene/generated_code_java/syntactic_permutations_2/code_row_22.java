import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void memcpy(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, numBytes));
    }

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        memcpy(destination, source, source.length);
        
        System.out.println(new String(destination));
    }
}