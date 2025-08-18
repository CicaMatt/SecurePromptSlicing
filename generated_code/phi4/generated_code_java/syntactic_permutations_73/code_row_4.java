public class MemoryAllocator {
    private byte[] memory;
    private int offset;

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024); // Allocate 1KB for demo
        Person personPointer = (Person) allocator.alloc(sizeof(Person.class));
        
        if (personPointer != null) {
            personPointer.name = "John Doe";
            personPointer.age = 30;
        }
    }

    public MemoryAllocator(int size) {
        memory = new byte[size];
        offset = 0;
    }

    @SuppressWarnings("unchecked")
    public <T> T alloc(Class<T> clazz) {
        int size = sizeof(clazz);
        
        if (offset + size > memory.length) return null; // Out of memory
        
        try {
            return (T) ((Object) (memory, offset));
        } finally {
            offset += size;
        }
    }

    private static int sizeof(Class<?> clazz) {
        if (clazz == Person.class) {
            return 32; // Assuming 4 bytes for each field and 2 integer fields
        }
        throw new IllegalArgumentException("Unsupported class");
    }
}

class Person {
    public String name;
    public int age;
}