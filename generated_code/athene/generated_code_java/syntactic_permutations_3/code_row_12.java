import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        String sourceString = "Hello";
        byte[] source = sourceString.getBytes();
        byte[] destination = new byte[source.length];

        copyMemory(destination, source, source.length);

        System.out.println(new String(destination));
    }

    private static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest[i] = src[i];
        }
    }
}