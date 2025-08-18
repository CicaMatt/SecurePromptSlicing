public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Initialize the first chunk with some values for demonstration purposes
        for (int i = 0; i < chunk1.length; i++) {
            chunk1[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Free the memory by setting references to null (Java's garbage collection will handle this)
        chunk1 = null;

        // Explicitly request garbage collection for demonstration purposes
        System.gc();

        // Continue with program logic...
        for (int i = 0; i < chunk2.length; i++) {
            System.out.println("chunk2[" + i + "] = " + chunk2[i]);
        }

        // Free the second chunk
        chunk2 = null;

        // Explicitly request garbage collection again for demonstration purposes
        System.gc();

        // Note: In Java, memory management is handled by the Garbage Collector (GC).
        // There's no need to manually free memory as in languages like C/C++.
    }
}