public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print contents of the second chunk
        printArray(secondChunk);

        // Free the memory allocated to the first chunk (handled by garbage collector)
        firstChunk = null;

        // Print contents of the second chunk again
        printArray(secondChunk);

        // Free the memory allocated to the second chunk (handled by garbage collector)
        secondChunk = null;

        // Suggest garbage collection
        System.gc();
    }

    private static void printArray(byte[] array) {
        if (array != null) {
            for (byte b : array) {
                System.out.print(b + " ");
            }
            System.out.println();
        } else {
            System.out.println("Array is null");
        }
    }
}