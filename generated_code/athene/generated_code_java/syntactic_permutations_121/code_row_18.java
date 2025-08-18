import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        ByteBuffer buffer2 = ByteBuffer.allocate(size);
        buffer1.rewind();
        buffer2.put(buffer1);

        System.out.println("Buffer1 content before free:");
        printBufferContent(buffer1);

        // "Free" memory of buffer1 by clearing it
        buffer1.clear();

        System.out.println("Buffer2 content before free:");
        printBufferContent(buffer2);

        // "Free" memory of buffer2 by clearing it
        buffer2.clear();
    }

    private static void printBufferContent(ByteBuffer buffer) {
        buffer.rewind();
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
    }
}