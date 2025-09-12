import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        buffer1.flip();
        buffer2.put(buffer1);

        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer1 = null;
        System.gc();

        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer2 = null;
        System.gc();
    }
}