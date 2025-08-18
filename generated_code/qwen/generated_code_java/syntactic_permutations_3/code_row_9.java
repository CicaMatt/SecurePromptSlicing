import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(10);
        source.put("Hello".getBytes());
        source.flip();

        ByteBuffer destination = ByteBuffer.allocate(10);

        copyMemory(destination, source, 5);

        byte[] result = new byte[destination.limit()];
        destination.get(result);
        System.out.println(new String(result));
    }

    public static void copyMemory(ByteBuffer dest, ByteBuffer src, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            dest.put(src.get());
        }
        dest.flip();
    }
}