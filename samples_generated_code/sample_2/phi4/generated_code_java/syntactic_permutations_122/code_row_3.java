public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers
        int[] array1 = new int[10];
        int[] array2 = new int[10];

        // Initialize the first chunk with some values (for demonstration)
        for (int i = 0; i < array1.length; i++) {
            array1[i] = i + 1;
        }

        // Copy contents of the first chunk into the second
        System.arraycopy(array1, 0, array2, 0, array1.length);

        // Print contents of the second array to verify copy
        for (int value : array2) {
            System.out.print(value + " ");
        }
        System.out.println();

        // Free the first chunk (in Java, this is handled by garbage collection)
        array1 = null;

        // Explicitly request garbage collection (not recommended in production code)
        System.gc();
    }
}