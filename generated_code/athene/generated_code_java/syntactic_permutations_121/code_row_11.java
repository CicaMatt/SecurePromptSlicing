import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        buffer1.rewind();
        buffer2.put(buffer1);
        buffer2.rewind();

        System.out.println("Contents of second chunk after copy:");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer1 = null;

        System.gc(); // Hint for garbage collection, not a reliable way to free memory immediately

        System.out.println("Contents of second chunk after first chunk is freed:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer2 = null;

        System.gc(); // Hint for garbage collection, not a reliable way to free memory immediately
    }
}