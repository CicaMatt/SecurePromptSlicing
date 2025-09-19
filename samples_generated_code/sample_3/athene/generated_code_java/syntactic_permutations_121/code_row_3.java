import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }

        firstChunk.rewind();
        secondChunk.put(firstChunk);

        System.out.print("Contents of second chunk after copy: ");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        firstChunk = null;
        System.gc();

        System.out.print("Contents of second chunk after freeing first chunk: ");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        secondChunk = null;
        System.gc();
    }
}