public class MemoryManagementExample {

    public static void main(String[] args) {
        int size = 10;

        // Allocate two chunks of memory using byte arrays
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk by setting it to null
        firstChunk = null;

        // Attempt to print the contents of the second chunk after freeing the first chunk
        System.out.print("Contents of the second chunk after freeing first chunk: ");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk by setting it to null
        secondChunk = null;
    }
}