import java.nio.ByteBuffer;

public class ByteCopier {

    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        String result = new String(destination);
        System.out.println(result);
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        if (dest == null || src == null || length < 0) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        if (length > src.length || length > dest.length) {
            throw new ArrayIndexOutOfBoundsException("Length exceeds array bounds");
        }

        System.arraycopy(src, 0, dest, 0, length);
    }
}