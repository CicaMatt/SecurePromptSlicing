import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] src = "Hello".getBytes();
        byte[] dest = new byte[src.length];

        // Copy bytes from source to destination
        copyBytes(dest, src, src.length);

        // Convert the buffer back to a string and print it
        System.out.println(new String(dest));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}