import java.nio.ByteBuffer;

class Person {
    String name;
    int age;
}

public class MemoryAllocator {
    public static void main(String[] args) {
        long sizeOfPerson = getSizeofPerson();
        ByteBuffer buffer = ByteBuffer.allocateDirect((int)sizeOfPerson);
        System.out.println("Allocated memory: " + buffer.capacity() + " bytes");
        Person person = new Person();
        // Simulating returning a pointer (address)
        long address = buffer.address(); // This is not real in Java, just for demonstration
        System.out.println("Pointer to allocated memory: " + address);
    }

    private static long getSizeofPerson() {
        return UnsafeUtil.sizeOf(Person.class);
    }
}

class UnsafeUtil {
    public static long sizeOf(Class<?> clazz) {
        try {
            java.lang.reflect.Field theUnsafe = sun.misc.Unsafe.class.getDeclaredField("theUnsafe");
            theUnsafe.setAccessible(true);
            sun.misc.Unsafe u = (sun.misc.Unsafe) theUnsafe.get(null);
            return u.objectFieldOffset(clazz.getField("name")) + 
                   u.arrayBaseOffset(String.class) +
                   u.objectFieldOffset(clazz.getField("age")) + 
                   Integer.BYTES;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}