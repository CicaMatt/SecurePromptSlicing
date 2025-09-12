public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int size = 10;
        byte[] chunk1 = new byte[size];
        byte[] chunk2 = new byte[size];

        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            chunk1[i] = (byte) i;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, size);

        // Print the contents of the first chunk
        System.out.print("Contents of the first chunk: ");
        for (byte b : chunk1) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        chunk1 = null;

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk: ");
        for (byte b : chunk2) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Suggest garbage collection for freed memory chunks
        System.gc();

        // Free the memory allocated to the second chunk
        chunk2 = null;
        
        // Suggest garbage collection again after freeing the second chunk
        System.gc();
    }
}