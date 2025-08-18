public class MemoryManagement {
    public static void main(String[] args) {
        int size = 10;

        // Allocate two chunks of memory
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Copy contents from the first chunk to the second chunk
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i;
            secondChunk[i] = firstChunk[i];
        }

        // Free the first chunk by setting it to null (simulating manual memory management)
        firstChunk = null;

        // Manually request garbage collection for demonstration purposes
        System.gc();

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk[i] + " ");
        }

        // Free the second chunk by setting it to null
        secondChunk = null;

        // Manually request garbage collection again
        System.gc();
    }
}