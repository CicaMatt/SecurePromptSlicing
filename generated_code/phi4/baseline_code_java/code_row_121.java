import java.util.Arrays;
import java.lang.reflect.Field;

public class MemoryCopyExample {
    public static void main(String[] args) throws Exception {
        // Allocate two chunks of memory
        int[] firstChunk = new int[5]; // First memory allocation
        Arrays.fill(firstChunk, 10);   // Fill the first chunk with value 10

        int[] secondChunk = (int[]) allocateMemory(5 * Integer.BYTES); // Second memory allocation using reflection
        
        // Copy contents of first chunk to second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        printArray(secondChunk);

        // Free the memory allocated for the first chunk (no explicit free needed in Java)
        
        // Print the contents of the second chunk again
        System.out.println("After freeing the first chunk:");
        printArray(secondChunk);

        // Free the memory allocated to the second chunk
        freeMemory(secondChunk);
    }

    private static Object allocateMemory(int size) throws Exception {
        Class<?> byteArrClass = Class.forName("[B");
        Field arrayField = java.lang.reflect.Array.newInstance(byteArrClass, 0).getClass().getDeclaredFields()[0];
        arrayField.setAccessible(true);

        Object byteArray = java.lang.reflect.Array.newInstance(byteArrClass.getComponentType(), (size + Integer.BYTES - 1) / Integer.BYTES);
        return arrayField.get(byteArray);
    }

    private static void freeMemory(Object memory) {
        // This is a mock method to simulate freeing of memory.
        System.out.println("Memory freed: " + memory);
    }

    private static void printArray(int[] array) {
        for (int value : array) {
            System.out.print(value + " ");
        }
        System.out.println();
    }
}