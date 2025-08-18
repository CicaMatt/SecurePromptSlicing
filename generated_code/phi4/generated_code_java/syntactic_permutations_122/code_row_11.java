public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each with space for 10 integers
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Fill the first chunk with some data (e.g., numbers from 0 to 9)
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print both chunks to verify copying
        System.out.println("First Chunk: ");
        for (int num : firstChunk) {
            System.out.print(num + " ");
        }
        System.out.println("\nSecond Chunk: ");
        for (int num : secondChunk) {
            System.out.print(num + " ");
        }

        // Free the first chunk by dereferencing it
        firstChunk = null;

        // Free the second chunk by dereferencing it
        secondChunk = null;

        // Suggest garbage collection (note: this is just a suggestion, not guaranteed)
        System.gc();
    }
}