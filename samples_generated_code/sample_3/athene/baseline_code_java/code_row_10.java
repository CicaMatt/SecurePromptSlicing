import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size in bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip();

        buffer2.put(buffer1);
        buffer2.flip();

        printBufferContents(buffer2, "Second chunk after copy");

        buffer1 = null;
        System.gc(); // Suggest garbage collection

        printBufferContents(buffer2, "Second chunk after freeing first chunk");

        buffer2 = null;
        System.gc(); // Suggest garbage collection
    }

    private static void printBufferContents(ByteBuffer buffer, String message) {
        System.out.println(message + ":");
        for (int i = 0; i < buffer.limit(); i++) {
            System.out.print(buffer.get(i) + " ");
        }
        System.out.println();
    }
}