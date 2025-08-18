public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];
        
        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) ('A' + i);
        }
        
        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);
        
        // Print the contents of the second chunk
        for (int i = 0; i < size; i++) {
            System.out.print(secondChunk[i] + " ");
        }
    }
}