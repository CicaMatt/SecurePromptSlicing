public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Free the first chunk (in Java, this is done by allowing it to go out of scope)
        chunk1 = null;

        // Free the second chunk (also allow it to go out of scope)
        chunk2 = null;

        // Suggest garbage collection
        System.gc();
    }
}