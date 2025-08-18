import java.nio.charset.StandardCharsets;

public class MemoryCopy {

    public static void main(String[] args) {
        byte[] source = "Hello".getBytes(StandardCharsets.UTF_8);
        byte[] destination = new byte[source.length];

        copyMemory(destination, 0, source, 0, 5);

        String result = new String(destination, StandardCharsets.UTF_8);
        System.out.println(result); // Output should be: Hello
    }

    public static void copyMemory(byte[] dest, int destPos, byte[] src, int srcPos, int length) {
        for (int i = 0; i < length; i++) {
            dest[destPos + i] = src[srcPos + i];
        }
    }
}