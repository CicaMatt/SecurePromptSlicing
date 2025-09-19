class Person {
    int status;

    public Person() {
        this.status = 0;
    }
}

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Example size, adjust as needed
    private byte[] memoryPool;
    private int nextFreeIndex;

    public MemoryAllocator(int size) {
        memoryPool = new byte[size];
        nextFreeIndex = 0;
    }

    @SuppressWarnings("unchecked")
    public <T> T allocate(Class<T> type, int size) {
        if (nextFreeIndex + size > MEMORY_SIZE) {
            throw new OutOfMemoryError("Not enough memory to allocate");
        }
        
        Object obj = null;
        try {
            obj = type.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            e.printStackTrace();
        }

        // Simulate storing object at the next free index
        // In a real scenario, you'd have more complex memory management
        int startIndex = nextFreeIndex;
        nextFreeIndex += size;

        return (T) obj;
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(MEMORY_SIZE);

        Person person = allocator.allocate(Person.class, 128); // Example size for a Person object
        System.out.println("Person status: " + person.status);
    }
}