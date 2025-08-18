public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate first chunk of memory (array)
        int[] firstChunk = new int[10];
        
        // Initialize first chunk with some values for demonstration
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 2;
        }
        
        // Allocate second chunk of memory (array)
        int[] secondChunk = new int[10];
        
        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);
        
        // Freeing memory: In Java, this is handled by Garbage Collector automatically.
        // However, we can make objects eligible for garbage collection by dereferencing them.
        firstChunk = null;
        secondChunk = null;
        
        // Suggest garbage collector to run (not guaranteed)
        System.gc();
    }
}