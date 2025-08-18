import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class MemoryChunks {
    public static void main(String[] args) {
        int size = 10;
        IntBuffer buffer1 = ByteBuffer.allocateDirect(size * Integer.BYTES).asIntBuffer();
        IntBuffer buffer2 = ByteBuffer.allocateDirect(size * Integer.BYTES).asIntBuffer();

        for (int i = 0; i < size; i++) {
            buffer1.put(i);
        }

        buffer2.put(buffer1);

        System.out.println("Contents of buffer1:");
        buffer1.rewind();
        while (buffer1.hasRemaining()) {
            System.out.print(buffer1.get() + " ");
        }
        System.out.println();

        buffer1 = null;
        System.gc(); // Suggestion for garbage collection, not guaranteed to free memory immediately

        System.out.println("Contents of buffer2:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        buffer2 = null;
        System.gc(); // Suggestion for garbage collection, not guaranteed to free memory immediately
    }
}