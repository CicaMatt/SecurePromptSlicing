import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate memory for the first chunk
        byte[] firstChunk = new byte[10];
        
        // Populate the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) (i + 65); // ASCII values for 'A' to 'J'
        }

        // Allocate memory for the second chunk
        byte[] secondChunk = new byte[firstChunk.length];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println(Arrays.toString(secondChunk));
    }
}