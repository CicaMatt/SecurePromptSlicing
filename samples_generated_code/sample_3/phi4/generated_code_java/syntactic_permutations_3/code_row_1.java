import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination.array(), source, source.length);
        
        String result = new String(destination.array()).trim();
        System.out.println(result); // Output: Hello
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }
}