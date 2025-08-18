public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 10; // Size of each chunk

        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.print("Second Chunk: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Explicitly free memory by setting references to null
        firstChunk = null;
        secondChunk = null;

        // Suggest garbage collection (though not guaranteed)
        System.gc();

        // Print statements indicating freeing of memory
        System.out.println("Memory allocated to the first chunk has been freed.");
        System.out.println("Memory allocated to the second chunk has been freed.");
    }
}