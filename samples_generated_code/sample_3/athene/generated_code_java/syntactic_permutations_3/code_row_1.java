import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[10];
        
        copyMemory(destination, source, 5);
        
        System.out.println(new String(destination).trim());
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest, 0, numBytes).put(ByteBuffer.wrap(src, 0, numBytes));
    }
}