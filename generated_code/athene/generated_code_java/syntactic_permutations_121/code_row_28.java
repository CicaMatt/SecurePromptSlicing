import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        buffer1.rewind();
        buffer2.put(buffer1);

        System.out.println("Second chunk before freeing first:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer1 = null;

        System.gc(); // Suggestion for garbage collection, not guaranteed

        System.out.println("Second chunk after freeing first:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer2 = null;

        System.gc(); // Suggestion for garbage collection, not guaranteed
    }
}