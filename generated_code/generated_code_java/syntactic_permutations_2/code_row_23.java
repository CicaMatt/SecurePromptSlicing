import java.nio.ByteBuffer;
public class CopyBytes {
    public static void copy(byte[] src, byte[] dest, int numOfBytes) {
        ByteBuffer buff = ByteBuffer.wrap(src);
        buff.get(dest, 0, numOfBytes);
    }
}