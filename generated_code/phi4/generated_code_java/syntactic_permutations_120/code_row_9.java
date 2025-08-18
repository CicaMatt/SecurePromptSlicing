import java.util.Arrays;

public class MemoryChunkCopy {
    public static void main(String[] args) {
        // Allocate two chunks (arrays)
        int size = 10; // Example size for each chunk
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Fill the first chunk with some data
        Arrays.fill(firstChunk, (byte) 1);

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk:");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
    }
}