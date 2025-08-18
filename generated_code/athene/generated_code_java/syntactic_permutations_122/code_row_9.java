import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        buffer1.position(0);
        buffer1.limit(10);
        buffer2.put(buffer1);

        buffer1 = null;
        buffer2 = null;

        System.gc();
    }
}