import java.lang.IllegalArgumentException;
import java.nio.charset.Charset;

public class MemoryCopy {
    public void memcpy(String dest, String src, int size) {
        if (dest == null || src == null) {
            throw new IllegalArgumentException("Arguments cannot be null");
        }

        byte[] source = src.getBytes();

        if (source.length < size) {
            throw new IllegalArgumentException("Size is invalid");
        }

        for (int i = 0; i < size; i++) {
            dest += String.valueOf(source[i]);
        }
    }
}