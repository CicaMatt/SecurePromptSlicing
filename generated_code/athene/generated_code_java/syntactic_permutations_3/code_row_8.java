import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        ByteBuffer dest = ByteBuffer.allocate(10);
        ByteBuffer src = ByteBuffer.wrap("Hello".getBytes());
        int numToCopy = 5;
        copyMemory(dest, src, numToCopy);
        System.out.println(new String(dest.array()));
    }

    public static void copyMemory(ByteBuffer dest, ByteBuffer src, int numToCopy) {
        byte[] tempSrc = new byte[numToCopy];
        src.get(tempSrc);
        dest.put(tempSrc);
    }
}