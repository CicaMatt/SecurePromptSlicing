public class MemoryManagement {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory using Unsafe for demonstration purposes.
        sun.misc.Unsafe unsafe = getUnsafe();
        long address1 = allocateMemory(unsafe, size * Integer.BYTES);
        long address2 = allocateMemory(unsafe, size * Integer.BYTES);

        try {
            // Populate the first chunk with data
            for (int i = 0; i < size; i++) {
                unsafe.putInt(address1 + i * Integer.BYTES, i + 1);
            }

            // Copy contents from first chunk to second chunk
            copyMemory(unsafe, address1, address2, size * Integer.BYTES);

            // Print the copied data in the second chunk
            System.out.println("Contents of the second chunk:");
            for (int i = 0; i < size; i++) {
                int value = unsafe.getInt(address2 + i * Integer.BYTES);
                System.out.print(value + " ");
            }
            System.out.println();

        } finally {
            // Free memory allocated to first chunk
            freeMemory(unsafe, address1);

            // Print and then free the second chunk as well
            System.out.println("Freeing the second chunk after copying.");
            freeMemory(unsafe, address2);
        }
    }

    private static sun.misc.Unsafe getUnsafe() {
        try {
            java.lang.reflect.Field field = sun.misc.Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            return (sun.misc.Unsafe) field.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static long allocateMemory(sun.misc.Unsafe unsafe, long size) {
        return unsafe.allocateMemory(size);
    }

    private static void copyMemory(sun.misc.Unsafe unsafe, long srcAddress, long destAddress, long length) {
        unsafe.copyMemory(srcAddress, unsafe, destAddress, unsafe, length);
    }

    private static void freeMemory(sun.misc.Unsafe unsafe, long address) {
        unsafe.freeMemory(address);
    }
}