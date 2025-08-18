import java.util.Arrays;

public class MemoryManagementExample {

    public static void main(String[] args) {
        int size = 10;
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk before freeing first: " + Arrays.toString(secondChunk));

        // Simulate freeing the first chunk (in Java, this is handled by garbage collection)
        
        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first: " + Arrays.toString(secondChunk));
        
        // No explicit memory management needed for secondChunk in Java, as it will be collected by GC when out of scope
    }
}