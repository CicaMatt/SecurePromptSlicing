import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class MemoryChunks {
    public static void main(String[] args) {
        int size = 1024; // Size of chunks in bytes

        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        System.out.println("Contents of chunk1:");
        chunk1.rewind();
        while (chunk1.hasRemaining()) {
            System.out.print(chunk1.get() + " ");
        }
        System.out.println();

        // Free memory allocated to chunk1
        FileChannel.map(FileChannel.MapMode.READ_ONLY, 0, 0); // Dummy call to force GC

        System.out.println("Contents of chunk2:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to chunk2
        FileChannel.map(FileChannel.MapMode.READ_ONLY, 0, 0); // Dummy call to force GC
    }
}