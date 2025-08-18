import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.rewind();

        ByteBuffer secondChunk = ByteBuffer.allocate(size);
        secondChunk.put(firstChunk);
        secondChunk.rewind();

        System.out.println("Contents of the second chunk after copy:");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        firstChunk = null;
        System.gc();

        System.out.println("Contents of the second chunk after freeing first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk.get() + " ");
        }
        System.out.println();

        secondChunk = null;
        System.gc();
    }
}