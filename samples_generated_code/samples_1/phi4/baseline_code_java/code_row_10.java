public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 5; // Size of each memory chunk

        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1); // Example data: 1, 2, 3, 4, 5
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk after copy
        System.out.print("Second chunk after copying: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk (Java does this automatically)
        firstChunk = null;

        // Print the contents of the second chunk after freeing the first chunk
        System.out.print("Second chunk after freeing first: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk (Java does this automatically)
        secondChunk = null;

        // Note: In Java, garbage collection handles memory deallocation
    }
}