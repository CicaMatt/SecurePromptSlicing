public class MemoryManagementExample {
    public static void main(String[] args) {
        int length = 10;
        
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[length];
        byte[] secondChunk = new byte[length];

        // Initialize the first chunk with some data
        for (int i = 0; i < length; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying:");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Freeing the memory allocated to the first chunk by making it null
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk:");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Freeing the memory allocated to the second chunk by making it null
        secondChunk = null;
    }
}