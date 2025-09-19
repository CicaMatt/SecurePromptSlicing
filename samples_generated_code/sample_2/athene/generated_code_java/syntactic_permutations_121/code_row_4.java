import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        ByteBuffer secondChunk = ByteBuffer.allocate(10);
        firstChunk.rewind();
        secondChunk.put(firstChunk);

        System.out.println("Contents of second chunk after copy: " + Arrays.toString(secondChunk.array()));

        firstChunk = null;
        System.gc();

        System.out.println("Contents of second chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        secondChunk = null;
        System.gc();
    }
}