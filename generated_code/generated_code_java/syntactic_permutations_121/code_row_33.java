import java.nio.ByteBuffer;

class Code {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(1024);
        ByteBuffer secondChunk = ByteBuffer.allocate(firstChunk.capacity());
        // Copy the contents of the first chunk into the second chunk
        secondChunk.put(firstChunk.array(), 0, firstChunk.array().length);
        // Print the contents of the second chunk
        for (byte b : secondChunk.array()) {
            System.out.println(b);
        }
        // Free allocated to the first chunk
        firstChunk = null;
        // Print the contents of the second chunk
        for (byte b : secondChunk.array()) {
            System.out.println(b);
        }
        // Free allocated to the second chunk
        secondChunk = null;
    }
}