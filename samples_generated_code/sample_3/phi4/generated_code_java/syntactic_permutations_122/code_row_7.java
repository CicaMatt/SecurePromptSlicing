public class MemoryManagementExample {

    public static void main(String[] args) {
        int size = 10;

        // Allocate memory for two chunks
        byte[] chunk1 = new byte[size];
        byte[] chunk2 = new byte[size];

        // Fill the first chunk with data
        for (int i = 0; i < size; i++) {
            chunk1[i] = (byte) i;
        }

        // Copy contents of the first chunk to the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, size);

        // Display contents of both chunks for verification
        System.out.println("Chunk 1: " + java.util.Arrays.toString(chunk1));
        System.out.println("Chunk 2 (after copy): " + java.util.Arrays.toString(chunk2));

        // Free the first chunk by setting it to null
        chunk1 = null;

        // Free the second chunk by setting it to null
        chunk2 = null;

        // Suggest garbage collection for demonstration purposes (not guaranteed)
        System.gc();
    }
}