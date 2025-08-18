import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryChunks {
    public static void main(String[] args) {
        int size = 1024; // Example size in bytes

        ByteBuffer firstChunk = ByteBuffer.allocateDirect(size);
        ByteBuffer secondChunk = ByteBuffer.allocateDirect(size);

        String content = "Hello, World!";
        byte[] contentBytes = content.getBytes(StandardCharsets.UTF_8);
        
        firstChunk.put(contentBytes);
        firstChunk.flip();

        secondChunk.put(firstChunk);

        System.out.println(new String(secondChunk.array(), StandardCharsets.UTF_8).trim());

        firstChunk.clear();
        secondChunk.flip();
        System.out.println(new String(secondChunk.array(), StandardCharsets.UTF_8).trim());
        
        // Freeing memory (Note: In Java, this is handled by the GC)
    }
}