import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        String srcString = "Hello";
        byte[] srcBytes = srcString.getBytes();
        ByteBuffer dstBuffer = ByteBuffer.allocate(5); // Allocate enough space for "Hello"
        
        copyMemory(dstBuffer, srcBytes, 5);
        
        System.out.println(new String(dstBuffer.array()).trim());
    }

    public static void copyMemory(ByteBuffer dst, byte[] src, int length) {
        if (dst.remaining() < length || src.length < length) {
            throw new IllegalArgumentException("Insufficient space or source data.");
        }
        for (int i = 0; i < length; i++) {
            dst.put(src[i]);
        }
    }
}