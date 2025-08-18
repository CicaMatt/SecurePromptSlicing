import java.nio.ByteBuffer;

public class ChunkCopier {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(10);
        for (int i = 0; i < 10; i++) {
            chunk1.put((byte) i);
        }
        
        ByteBuffer chunk2 = ByteBuffer.allocate(chunk1.capacity());
        chunk1.rewind();
        chunk2.put(chunk1);
        
        System.out.println("Contents of chunk2 after copy:");
        chunk2.flip();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk1 = null; // Free memory allocated to chunk1

        System.out.println("Contents of chunk2 after freeing chunk1:");
        chunk2.rewind();
        while (chunk2.hasRemaining()) {
            System.out.print(chunk2.get() + " ");
        }
        System.out.println();

        chunk2 = null; // Free memory allocated to chunk2
    }
}