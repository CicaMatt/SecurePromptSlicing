public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int size = 5;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.print("Second chunk after copy: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk (in Java, this is automatic)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.print("Second chunk after freeing first: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        secondChunk = null;

        // At this point, both chunks are freed and no further action needed.
    }
}