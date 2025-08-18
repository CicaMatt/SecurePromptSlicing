public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate first chunk of memory
        int[] firstChunk = new int[10];
        
        // Initialize the first chunk with some values (for demonstration)
        for (int i = 0; i < 10; i++) {
            firstChunk[i] = i;
        }

        // Allocate second chunk of memory
        int[] secondChunk = new int[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, 10);

        // "Free" the first chunk (in Java, this is done by dereferencing)
        firstChunk = null;

        // Suggest garbage collection for cleanup (though not guaranteed)
        System.gc();

        // Print contents of second chunk to verify copy
        for (int value : secondChunk) {
            System.out.println(value);
        }

        // "Free" the second chunk
        secondChunk = null;

        // Suggest garbage collection again
        System.gc();
    }
}