import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        firstChunk.rewind();
        secondChunk.put(firstChunk);

        System.out.println("Contents of second chunk after copy:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        firstChunk = null;
        System.gc();

        System.out.println("Contents of second chunk after freeing first chunk:");
        secondChunk.rewind();
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        secondChunk = null;
        System.gc();
    }
}