import java.nio.ByteBuffer;
import java.util.Arrays;

public class ByteCopier {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        copyBytes(destination, source, source.length);
        
        System.out.println(Arrays.toString(destination));  // Output: [72, 101, 108, 108, 111, 44, 32, 87, 111, 114, 108, 100, 33]
    }

    public static void copyBytes(byte[] destination, byte[] source, int length) {
        for (int i = 0; i < length; i++) {
            destination[i] = source[i];
        }
    }
}