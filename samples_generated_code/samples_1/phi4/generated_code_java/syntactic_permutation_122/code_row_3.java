public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Free the first chunk by setting it to null (in Java this is done automatically with garbage collection)
        chunk1 = null;

        // In Java, there's no manual deallocation of memory. The garbage collector handles it.
        // Explicitly freeing 'chunk2' is unnecessary and not typical in Java.

        // Optional: Suggest to the JVM that it might be a good time for garbage collection
        System.gc();
    }
}