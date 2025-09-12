import java.util.Arrays;

class Person {
    String name;
    int age;

    Person(String name, int age) {
        this.name = name;
        this.age = age;
    }
}

public class MemoryAllocator {

    private static byte[] memoryPool;
    private static int nextFreeIndex = 0;

    public static void initializeMemoryPool(int size) {
        memoryPool = new byte[size];
    }

    @SuppressWarnings("unchecked")
    public static <T> T allocate(Class<T> clazz) {
        int size = getMemorySize(clazz);
        if (nextFreeIndex + size > memoryPool.length) {
            throw new OutOfMemoryError("Not enough memory in pool to allocate " + clazz.getSimpleName());
        }

        byte[] block = Arrays.copyOfRange(memoryPool, nextFreeIndex, nextFreeIndex + size);
        T obj = clazz.cast(loadObjectFromBytes(block, clazz));
        nextFreeIndex += size;
        
        return obj;
    }

    private static int getMemorySize(Class<?> clazz) {
        if (clazz == Person.class) {
            return 24; // Estimated size for a Person object in bytes: String reference + integer
        }
        throw new IllegalArgumentException("Unsupported class type");
    }

    @SuppressWarnings("unchecked")
    private static Object loadObjectFromBytes(byte[] bytes, Class<?> clazz) {
        if (clazz == Person.class) {
            int age = byteArrayToInt(Arrays.copyOfRange(bytes, 0, Integer.BYTES));
            String name = new String(Arrays.copyOfRange(bytes, Integer.BYTES, bytes.length), java.nio.charset.StandardCharsets.UTF_8);
            return new Person(name, age);
        }
        throw new IllegalArgumentException("Unsupported class type");
    }

    private static int byteArrayToInt(byte[] bytes) {
        if (bytes.length != Integer.BYTES) {
            throw new IllegalArgumentException("Byte array length is not equal to integer size");
        }
        return ((bytes[0] & 0xFF) << 24) |
               ((bytes[1] & 0xFF) << 16) |
               ((bytes[2] & 0xFF) << 8)  |
               (bytes[3] & 0xFF);
    }

    public static void main(String[] args) {
        initializeMemoryPool(1024); // Initialize memory pool with 1KB

        Person person = allocate(Person.class);
        person.name = "John Doe";
        person.age = 30;

        System.out.println("Allocated Person: " + person.name + ", Age: " + person.age);
    }
}