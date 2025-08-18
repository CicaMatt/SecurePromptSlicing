import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(1024);
        ByteBuffer buffer2 = ByteBuffer.allocate(1024);

        for (int i = 0; i < 1024; i++) {
            buffer1.put((byte) i);
        }

        buffer1.rewind();
        buffer2.put(buffer1);
        buffer2.rewind();

        printBufferContents(buffer2);

        buffer1.clear();
        buffer1 = null;

        printBufferContents(buffer2);

        buffer2.clear();
        buffer2 = null;
    }

    private static void printBufferContents(ByteBuffer buffer) {
        buffer.mark();
        while (buffer.position() < buffer.limit()) {
            System.out.print(buffer.get() + " ");
        }
        System.out.println();
        buffer.reset();
    }
}