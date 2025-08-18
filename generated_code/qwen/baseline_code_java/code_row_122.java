import java.nio.ByteBuffer;
import sun.misc.Unsafe;

public class MemoryManipulation {
    private static final Unsafe UNSAFE = getUnsafe();

    private static Unsafe getUnsafe() {
        try {
            java.lang.reflect.Field field = Unsafe.class.getDeclaredField("theUnsafe");
            field.setAccessible(true);
            return (Unsafe) field.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        long size = 10;
        
        // Allocate first chunk
        long address1 = UNSAFE.allocateMemory(size);
        ByteBuffer buffer1 = ByteBuffer.wrap(new byte[(int) size]);
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }
        UNSAFE.copyMemory(buffer1.array(), Unsafe.ARRAY_BYTE_BASE_OFFSET, null, address1, size);

        // Allocate second chunk
        long address2 = UNSAFE.allocateMemory(size);

        // Copy contents from first chunk to second chunk
        UNSAFE.copyMemory(null, address1, null, address2, size);

        // Free the first chunk
        UNSAFE.freeMemory(address1);

        // Free the second chunk
        UNSAFE.freeMemory(address2);
    }
}