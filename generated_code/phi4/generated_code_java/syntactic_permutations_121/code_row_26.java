public class MemoryCopy {

    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk:");
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        secondChunk = null;

        // Attempting garbage collection manually (not guaranteed)
        System.gc();
    }
}