import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "This is a test string.".getBytes();
        byte[] destination = new byte[source.length];

        int bytesToCopy = 10;
        
        copyBytes(destination, source, bytesToCopy);

        System.out.println(new String(destination).trim());
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        ByteBuffer bufferSrc = ByteBuffer.wrap(src);
        ByteBuffer bufferDest = ByteBuffer.allocate(length).put(dest, 0, Math.min(length, dest.length));
        
        for (int i = 0; i < length && !bufferSrc.hasRemaining(); i++) {
            bufferDest.put(bufferSrc.get());
        }
    }
}