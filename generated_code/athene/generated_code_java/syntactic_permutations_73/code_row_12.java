import java.nio.ByteBuffer;
import java.nio.channels CLOSED_CHANNEL;

public class MemoryAllocation {
    static class Person {
        String name;
        int age;
    }

    public static void main(String[] args) {
        long sizeOfPerson = (long) (1.0 * ((ByteBuffer.allocateDirect(1).capacity() * 8) / (double) Unsafe.ARRAY_BYTE_BASE_OFFSET)) * (Unsafe.ARRAY_BYTE_INDEX_SCALE * 2 + Unsafe.ARRAY_BYTE_BASE_OFFSET);
        sun.misc.Unsafe unsafe = getUnsafe();
        long address = unsafe.allocateMemory(sizeOfPerson);
        System.out.println("Allocated memory at address: " + address);
    }

    private static sun.misc.Unsafe getUnsafe() {
        try {
            java.lang.reflect.Field f = sun.misc.Unsafe.class.getDeclaredField("theUnsafe");
            f.setAccessible(true);
            return (sun.misc.Unsafe) f.get(null);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}