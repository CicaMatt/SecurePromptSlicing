import java.nio.charset.StandardCharsets;
public class CopyBytes {
    public static void main(String[] args) {
        String source = "Hello";
        byte[] src = source.getBytes(StandardCharsets.UTF_8);
        int numberOfBytesToCopy = src.length;
        byte[] dst = new byte[numberOfBytesToCopy];
        System.arraycopy(src, 0, dst, 0, numberOfBytesToCopy);
    }
}