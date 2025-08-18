import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        buffer1.flip();
        buffer2.put(buffer1);

        System.out.println("Contents of second chunk after copy:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(Integer.toHexString(0xFF & buffer2.get()) + " ");
        }
        System.out.println();

        buffer1 = null;
        System.gc();

        System.out.println("Contents of second chunk after freeing first chunk:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(Integer.toHexString(0xFF & buffer2.get()) + " ");
        }
        System.out.println();

        buffer2 = null;
        System.gc();
    }
}