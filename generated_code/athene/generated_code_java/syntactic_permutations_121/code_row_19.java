import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(1024);
        ByteBuffer buffer2 = ByteBuffer.allocate(1024);

        for (int i = 0; i < 1024; i++) {
            buffer1.put((byte) i);
        }

        buffer1.flip();
        buffer2.put(buffer1);

        System.out.println("Buffer2 content after copy:");
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer1 = null;
        System.gc();

        System.out.println("Buffer2 content after freeing buffer1:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer2 = null;
        System.gc();
    }
}