public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory using arrays
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Fill the first chunk with example data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        for (int value : secondChunk) {
            System.out.println(value);
        }
    }
}