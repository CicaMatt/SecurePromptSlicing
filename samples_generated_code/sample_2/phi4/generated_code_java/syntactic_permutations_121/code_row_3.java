public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 5;
        
        // Allocate two chunks of memory
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        for (int value : secondChunk) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk (in Java, this is handled by garbage collector)
        firstChunk = null;

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after freeing first chunk:");
        for (int value : secondChunk) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk (in Java, this is handled by garbage collector)
        secondChunk = null;

        // Suggesting garbage collection (not guaranteed to be executed immediately)
        System.gc();
    }
}