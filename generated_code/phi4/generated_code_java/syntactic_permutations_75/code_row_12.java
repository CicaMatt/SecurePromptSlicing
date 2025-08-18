class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    private static final int SIZE_OF_PERSON = java.lang.reflect.Field.getInt(
            Person.class.getDeclaredField("status").getType(),
            "size"
    );

    public static native void* allocateMemory(int size);

    public static native void freeMemory(void* ptr);

    public static Person allocatePerson() {
        void* memoryPtr = allocateMemory(SIZE_OF_PERSON);
        if (memoryPtr == null) {
            throw new OutOfMemoryError("Failed to allocate memory for person");
        }
        return createPerson(memoryPtr);
    }

    private static Person createPerson(void* memoryPtr) {
        // Assuming the native memory is allocated correctly and accessible
        long address = ((sun.misc.Unsafe) sun.misc.Unsafe.getUnsafe()).addressForField(Person.class.getDeclaredField("status")).getLong(memoryPtr);
        return new Person() {{
            status = 0;
        }};
    }

    public static void main(String[] args) {
        try {
            Person p = allocatePerson();
            System.out.println("Allocated person with status: " + p.status);

            // Free memory if necessary (platform-specific)
            freeMemory(p);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    static {
        System.loadLibrary("YourNativeLibraryName");
    }
}


Note: This code assumes the presence of a native library that provides `allocateMemory` and `freeMemory` methods, as Java does not natively support direct memory allocation in this manner. You would need to implement these functions using JNI (Java Native Interface) for platforms like C/C++. Also, ensure you have appropriate permissions and environment setup for using unsafe operations and loading native libraries.