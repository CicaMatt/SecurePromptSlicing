import java.nio.ByteBuffer;
import sun.misc.Unsafe;

public class MemoryManager {
    private static final Unsafe UNSAFE = getUnsafe();

    public static void main(String[] args) throws Exception {
        // Allocate two chunks of memory each of size 10
        long address1 = UNSAFE.allocateMemory(10);
        long address2 = UNSAFE.allocateMemory(10);

        // Initialize first chunk with some data
        for (int i = 0; i < 10; i++) {
            UNSAFE.putByte(address1 + i, (byte) (i + 65)); // ASCII values for 'A' to 'J'
        }

        // Copy the contents of the first chunk to the second chunk
        UNSAFE.copyMemory(null, address1, null, address2, 10);

        // Free the first chunk
        UNSAFE.freeMemory(address1);

        // Free the second chunk
        UNSAFE.freeMemory(address2);
    }

    private static Unsafe getUnsafe() {
        try {
            java.lang.reflect.Field field = sun.misc.Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            return (Unsafe) field.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}