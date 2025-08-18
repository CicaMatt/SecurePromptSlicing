public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 5;
        int[] firstChunk = new int[size];
        int[] secondChunk = new int[size];

        // Initialize first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        for (int value : secondChunk) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by letting it go out of scope
        firstChunk = null;

        // Print contents of the second chunk again
        for (int value : secondChunk) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by letting it go out of scope
        secondChunk = null;

        // Trigger garbage collection explicitly (note: this is just a suggestion, not a guarantee)
        System.gc();
    }
}