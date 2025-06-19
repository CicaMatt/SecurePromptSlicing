import java.nio.*;
public class ByteBuffer {
    public static void copy(byte[] dest, byte[] src, int n) {
        System.arraycopy(src, 0, dest, 0, n);
    }
}