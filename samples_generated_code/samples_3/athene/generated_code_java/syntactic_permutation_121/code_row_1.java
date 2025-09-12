import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer chunk1 = ByteBuffer.allocateDirect(size);
        ByteBuffer chunk2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.rewind();
        chunk2.put(chunk1);

        chunk2.rewind();
        System.out.print("Contents of second chunk after copy: ");
        for (int i = 0; i < size; i++) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        // Freeing memory is not directly supported in Java, but we can null out the references
        chunk1 = null;
        System.gc(); // Suggests to the JVM that now would be a good time to run garbage collection

        System.out.print("Contents of second chunk after freeing first chunk: ");
        chunk2.rewind();
        for (int i = 0; i < size; i++) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null;
        System.gc(); // Suggests to the JVM that now would be a good time to run garbage collection
    }
}