import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        String srcString = "Hello";
        byte[] srcBytes = srcString.getBytes();
        byte[] destBytes = new byte[srcBytes.length];
        
        copyMemory(destBytes, srcBytes, srcBytes.length);
        
        System.out.println(new String(destBytes));
    }

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        ByteBuffer.wrap(src).get(dest, 0, numBytes);
    }
}