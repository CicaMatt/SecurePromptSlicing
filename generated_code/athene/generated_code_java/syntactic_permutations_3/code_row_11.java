import java.nio.charset.StandardCharsets;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes(StandardCharsets.UTF_8);
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(new String(destination, StandardCharsets.UTF_8));
    }

    public static void copyBytes(byte[] dest, byte[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }
}