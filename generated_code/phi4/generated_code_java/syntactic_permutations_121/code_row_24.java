public class MemoryCopy {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocating two chunks of memory
        int[] firstChunk = new int[size];
        int[] secondChunk;

        // Filling the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        // Copying contents of the first chunk to the second chunk
        secondChunk = new int[size];
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Printing contents of the second chunk
        printArray(secondChunk);

        // Freeing memory by making references null (simulated in Java)
        firstChunk = null;
        // Attempt to print the contents of the second chunk after freeing the first one
        System.out.println("Contents of the second chunk after freeing first:");
        printArray(secondChunk);

        // Freeing memory allocated to the second chunk
        secondChunk = null;

        // Attempt to access the second chunk (this would cause a NullPointerException if uncommented)
        // System.out.println("Attempting to access freed second chunk:");
        // printArray(secondChunk);
    }

    private static void printArray(int[] array) {
        if (array != null) {
            for (int value : array) {
                System.out.print(value + " ");
            }
            System.out.println();
        } else {
            System.out.println("Array is null");
        }
    }
}