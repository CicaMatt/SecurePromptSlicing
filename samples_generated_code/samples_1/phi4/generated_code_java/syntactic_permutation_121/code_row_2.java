public class MemoryManipulation {

    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory using arrays
        byte[] firstChunk = new byte[size];
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);  // Fill with some values
        }

        byte[] secondChunk = new byte[size];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        printArray(secondChunk);

        // Free memory allocated to the first chunk (in Java, this is done by garbage collection)
        firstChunk = null;

        // Print contents of the second chunk again
        printArray(secondChunk);
        
        // Suggest garbage collection (not guaranteed)
        System.gc();
    }

    private static void printArray(byte[] array) {
        for (byte b : array) {
            System.out.print(b + " ");
        }
        System.out.println();
    }
}