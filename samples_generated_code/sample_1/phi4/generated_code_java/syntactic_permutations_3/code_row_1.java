import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        ByteBuffer destination = ByteBuffer.allocate(source.length);

        copyBytes(destination, source, source.length);

        String result = new String(destination.array()).trim();
        System.out.println(result);
    }

    private static void copyBytes(ByteBuffer destination, byte[] source, int length) {
        for (int i = 0; i < length; i++) {
            destination.put(source[i]);
        }
    }
}