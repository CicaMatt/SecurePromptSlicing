import java.lang.reflect.Field;

public class MemoryManager {

    public static void main(String[] args) throws Exception {
        // Allocate two chunks of memory, each of size 10 bytes.
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[10];

        // Initialize the first chunk with some data
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk to the second chunk.
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Free the first chunk by clearing its reference
        firstChunk = null;

        // Force garbage collection for demonstration purposes (note: this is just a suggestion and not guaranteed)
        System.gc();

        // Free the second chunk by clearing its reference
        secondChunk = null;
        
        // Force garbage collection again
        System.gc();
    }
}


This Java code allocates two byte arrays each of size 10, copies data from the first to the second, and then "frees" them by setting their references to `null`, which allows for potential garbage collection. Note that explicit memory management like in languages such as C/C++ is not typically done in Java; instead, it relies on automatic garbage collection.