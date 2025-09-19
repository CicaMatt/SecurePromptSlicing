import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate memory for the first chunk (e.g., 10 bytes)
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        
        // Fill the first chunk with some data
        byte[] data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        firstChunk.put(data);

        // Allocate memory for the second chunk (e.g., same size as the first)
        ByteBuffer secondChunk = ByteBuffer.allocate(10);
        
        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk.array(), 0, firstChunk.remaining());

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk after copy: " + bytesToString(secondChunk.array()));

        // Free memory allocated to the first chunk (implicitly done by garbage collector)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk: " + bytesToString(secondChunk.array()));

        // Free memory allocated to the second chunk (implicitly done by garbage collector)
        secondChunk = null;
    }

    private static String bytesToString(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(b).append(" ");
        }
        return sb.toString().trim();
    }
}