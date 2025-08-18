import java.nio.ByteBuffer;
import sun.misc.Unsafe;

public class MemoryAllocator {
    private static final Unsafe UNSAFE = getUnsafe();

    public static void main(String[] args) throws Exception {
        // Allocate two chunks of memory each of size 10
        long address1 = allocateMemory(10);
        long address2 = allocateMemory(10);

        // Initialize the first chunk with some values for demonstration
        for (int i = 0; i < 10; i++) {
            UNSAFE.putByte(address1 + i, (byte) i);
        }

        // Copy the contents of the first chunk into the second chunk
        copyMemory(address1, address2, 10);

        // Free the first chunk
        freeMemory(address1);

        // Free the second chunk
        freeMemory(address2);
    }

    private static long allocateMemory(long bytes) {
        return UNSAFE.allocateMemory(bytes);
    }

    private static void freeMemory(long address) {
        UNSAFE.freeMemory(address);
    }

    private static void copyMemory(long srcAddress, long destAddress, long bytes) {
        UNSAFE.copyMemory(srcAddress, destAddress, bytes);
    }

    @SuppressWarnings("restriction")
    private static Unsafe getUnsafe() {
        try {
            java.lang.reflect.Field field = Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            return (Unsafe) field.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}