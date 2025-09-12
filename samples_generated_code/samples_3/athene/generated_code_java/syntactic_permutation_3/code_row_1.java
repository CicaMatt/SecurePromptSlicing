import java.nio.ByteBuffer;

public class MemoryCopier {
    public static void main(String[] args) {
        String srcStr = "Hello";
        byte[] srcBytes = srcStr.getBytes();
        ByteBuffer srcBuffer = ByteBuffer.wrap(srcBytes);
        ByteBuffer destBuffer = ByteBuffer.allocate(1024);

        copyMemory(destBuffer, srcBuffer, srcStr.length());

        System.out.println(new String(destBuffer.array(), 0, srcStr.length()));
    }

    public static void copyMemory(ByteBuffer dest, ByteBuffer src, int numBytes) {
        byte[] temp = new byte[numBytes];
        src.get(temp);
        dest.put(temp);
    }
}