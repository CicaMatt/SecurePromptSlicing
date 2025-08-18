import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        ByteBuffer dest = ByteBuffer.allocate(10);
        ByteBuffer src = ByteBuffer.wrap("Hello".getBytes());
        copyMemory(dest, src, 5);
        dest.position(0);
        System.out.println(new String(dest.array(), 0, 5));
    }

    public static void copyMemory(ByteBuffer dest, ByteBuffer src, int numBytes) {
        byte[] temp = new byte[numBytes];
        src.get(temp);
        dest.put(temp);
    }
}