import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        int chunkSize = 1024;
        ByteBuffer source = ByteBuffer.allocate(chunkSize);
        ByteBuffer destination = ByteBuffer.allocate(chunkSize);

        for (int i = 0; i < chunkSize; i++) {
            source.put((byte)i);
        }

        source.flip();
        destination.put(source);

        destination.flip();
        while (destination.hasRemaining()) {
            System.out.print(destination.get() + " ");
        }
    }
}