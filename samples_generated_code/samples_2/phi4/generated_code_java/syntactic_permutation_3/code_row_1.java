import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        ByteBuffer destination = ByteBuffer.allocate(10);
        byte[] source = "Hello".getBytes();
        
        copyBytes(destination, source, 5);

        System.out.println(new String(destination.array(), 0, 5));
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest.put(src[i]);
        }
    }
}