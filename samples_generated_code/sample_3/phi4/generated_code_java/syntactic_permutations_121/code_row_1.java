public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Example size for memory chunks

        // Allocate two chunks of memory
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        printArray(secondChunk);

        // Free the memory allocated to the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        printArray(secondChunk);

        // Free the memory allocated to the second chunk
        secondChunk = null;

        // Suggest to the JVM that it run the garbage collector
        System.gc();
    }

    private static void printArray(int[] array) {
        for (int value : array) {
            System.out.print(value + " ");
        }
        System.out.println();  // Move to a new line after printing all elements
    }
}