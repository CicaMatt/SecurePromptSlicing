import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "This is a test string.".getBytes();
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(new String(destination));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        ByteBuffer destBuffer = ByteBuffer.wrap(dest);
        ByteBuffer srcBuffer = ByteBuffer.wrap(src);

        for (int i = 0; i < length; i++) {
            destBuffer.put(i, srcBuffer.get(i));
        }
    }
}