public class MemoryCopyExample {

    public static void main(String[] args) {
        int size = 10;

        // Allocate first chunk of memory
        byte[] firstChunk = new byte[size];
        
        // Initialize first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Allocate second chunk of memory
        byte[] secondChunk = new byte[size];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Use or print the copied data from the second chunk
        for (byte b : secondChunk) {
            System.out.print(b + " ");
        }
        
        System.out.println();

        // No explicit free necessary in Java as garbage collector handles it.
    }
}