public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some values (for example, 0 to 9)
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) i;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk[i] + " ");
        }
    }
}