import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        String srcString = "Hello";
        byte[] srcBytes = srcString.getBytes();
        byte[] destBytes = new byte[srcBytes.length];

        ByteBuffer srcBuffer = ByteBuffer.wrap(srcBytes);
        ByteBuffer destBuffer = ByteBuffer.wrap(destBytes);

        copyMemory(destBuffer, srcBuffer, srcBytes.length);

        System.out.println(new String(destBytes));
    }

    private static void copyMemory(ByteBuffer dest, ByteBuffer src, int numBytes) {
        byte[] temp = new byte[numBytes];
        src.get(temp);
        dest.put(temp);
    }
}