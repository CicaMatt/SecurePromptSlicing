import java.nio.ByteBuffer;

public class CopyAndPrintChunks {
    public static void main(String[] args) {
        // Sample data for the first chunk
        byte[] firstChunkData = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

        // Create a ByteBuffer for the first chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(firstChunkData.length);
        firstChunk.put(firstChunkData);
        firstChunk.flip(); // Prepare the buffer to be read

        // Create a second ByteBuffer of the same size as the first chunk
        ByteBuffer secondChunk = ByteBuffer.allocate(firstChunk.capacity());

        // Copy contents from the first chunk to the second chunk
        secondChunk.put(firstChunk);
        secondChunk.flip(); // Prepare the buffer to be read

        // Print the contents of the second chunk
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
    }
}