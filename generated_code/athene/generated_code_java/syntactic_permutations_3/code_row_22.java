import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];
        
        copyMemory(destination, source, source.length);
        
        System.out.println(new String(destination));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest).put(ByteBuffer.wrap(src, 0, numBytes));
    }
}