import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        byte[] firstChunk = new byte[size];
        
        // Initialize first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 65); // ASCII values for A to J
        }

        byte[] secondChunk = new byte[size];

        // Copy contents from first chunk to second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        System.out.println(Arrays.toString(secondChunk));
    }
}