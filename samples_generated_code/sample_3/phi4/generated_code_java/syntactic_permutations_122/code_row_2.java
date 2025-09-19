import java.util.Arrays;

public class MemoryAllocator {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Free the first chunk by making it eligible for garbage collection
        chunk1 = null;

        // Free the second chunk by making it eligible for garbage collection
        chunk2 = null;

        // Request garbage collection (note: this is just a request; JVM decides when to run GC)
        System.gc();
        
        // Optional: Just to simulate some activity and increase chances of seeing GC in action
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}