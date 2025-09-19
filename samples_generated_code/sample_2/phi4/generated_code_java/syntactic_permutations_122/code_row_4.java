public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers.
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Initialize the first chunk with some values.
        for (int i = 0; i < chunk1.length; i++) {
            chunk1[i] = i + 1;
        }

        // Copy contents of the first chunk to the second chunk.
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Free the first chunk by making it eligible for garbage collection.
        chunk1 = null;

        // Free the second chunk as well by making it eligible for garbage collection.
        chunk2 = null;

        // Suggest to JVM to perform garbage collection (for demonstration purposes).
        System.gc();

        System.out.println("Chunks have been freed.");
    }
}