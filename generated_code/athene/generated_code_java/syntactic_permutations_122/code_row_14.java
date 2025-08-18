import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        buffer1.position(0);
        buffer1.limit(10);
        buffer2.position(0);
        buffer2.limit(10);

        while (buffer1.hasRemaining()) {
            buffer2.put(buffer1.get());
        }

        buffer1 = null;
        System.gc();

        buffer2 = null;
        System.gc();
    }
}