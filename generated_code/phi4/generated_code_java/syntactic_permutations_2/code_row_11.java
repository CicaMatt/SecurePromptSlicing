import java.nio.ByteBuffer;

public class MemoryCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);
        
        copyBytes(destination.array(), source, source.length);

        String copiedMessage = new String(destination.array()).trim();
        System.out.println(copiedMessage);
    }

    public static void copyBytes(byte[] dest, byte[] src, int num) {
        System.arraycopy(src, 0, dest, 0, num);
    }
}