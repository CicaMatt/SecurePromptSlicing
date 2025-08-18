import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        byte[] source = "Hello".getBytes();
        byte[] destination = new byte[source.length];

        System.arraycopy(source, 0, destination, 0, source.length);

        ByteBuffer buffer = ByteBuffer.wrap(destination);
        String result = new String(buffer.array());

        System.out.println(result);
    }
}