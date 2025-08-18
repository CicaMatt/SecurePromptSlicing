import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] dest = new byte[20];
        byte[] src = "Hello".getBytes();
        
        copyMemory(dest, src, 5);
        
        System.out.println(new String(dest).trim());
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(dest, 0, numBytes).put(ByteBuffer.wrap(src, 0, numBytes));
    }
}