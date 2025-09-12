import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String original = "Hello";
        ByteBuffer srcBuffer = ByteBuffer.allocate(original.getBytes().length);
        srcBuffer.put(original.getBytes());
        srcBuffer.flip();

        ByteBuffer destBuffer = ByteBuffer.allocate(srcBuffer.capacity());

        copyBytes(destBuffer, srcBuffer, srcBuffer.remaining());

        byte[] resultArray = new byte[destBuffer.capacity()];
        destBuffer.get(resultArray);

        System.out.println(new String(resultArray));
    }

    public static void copyBytes(ByteBuffer destination, ByteBuffer source, int numberOfBytes) {
        for (int i = 0; i < numberOfBytes; i++) {
            destination.put(source.get());
        }
    }
}