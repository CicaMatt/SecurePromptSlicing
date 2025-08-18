import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "This is a test message.".getBytes();
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(new String(destination));
    }
    
    public static void copyBytes(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        srcBuffer.limit(numBytes).position(0);
        destBuffer.put(srcBuffer);
    }
}