import java.nio.*;
public class ByteBuffer {
    public static void copyBytes(ByteBuffer src, int position, int length) {
        for (int i = 0; i < length; i++)
            src[position + i] = msg[i];
    }
}