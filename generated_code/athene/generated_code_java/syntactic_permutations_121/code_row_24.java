import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(1024);
        ByteBuffer chunk2 = ByteBuffer.allocate(1024);

        for (int i = 0; i < 1024; i++) {
            chunk1.put((byte) i);
        }

        chunk1.rewind();
        chunk2.put(chunk1);

        chunk2.rewind();
        System.out.println("Contents of chunk2 before free:");
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        // Java does not have a direct way to 'free' memory like in C/C++.
        // However, we can make the buffer eligible for garbage collection by nulling references.
        chunk1 = null;

        System.out.println("Contents of chunk2 after freeing chunk1:");
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null;
    }
}