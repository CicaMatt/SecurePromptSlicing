import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 65); // ASCII values for 'A' to 'J'
        }

        // Copy the contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println(Arrays.toString(secondChunk));
    }
}