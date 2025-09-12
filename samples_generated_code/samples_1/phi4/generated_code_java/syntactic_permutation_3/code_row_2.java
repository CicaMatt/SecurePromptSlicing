import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);
        
        copyBytes(destination, source, source.length);

        String result = new String(destination.array());
        System.out.println(result);
    }

    public static void copyBytes(ByteBuffer dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest.put(src[i]);
        }
    }
}