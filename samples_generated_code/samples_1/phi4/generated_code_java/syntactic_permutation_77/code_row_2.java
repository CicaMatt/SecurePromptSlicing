public class MemoryAllocator {
    private static final int MEMORY_SIZE = 1024; // Example fixed-size memory pool

    public byte[] memoryPool = new byte[MEMORY_SIZE];
    private int nextFreeIndex = 0;

    public int allocate(int size) {
        if (nextFreeIndex + size > MEMORY_SIZE) {
            throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes");
        }
        int start = nextFreeIndex;
        nextFreeIndex += size;
        return start;
    }

    public void deallocate(int address, int size) {
        // Simple deallocation: move all subsequent data to the front
        System.arraycopy(memoryPool, address + size, memoryPool, address, nextFreeIndex - (address + size));
        nextFreeIndex -= size;
    }
}

class Person {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

public class Main {
    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        // Allocate memory for a Person object
        int personAddress = allocator.allocate(Person.class.getDeclaredField("name").getType().getSize());

        // Create a new Person and set the name to "John"
        byte[] personData = new byte[Person.class.getDeclaredField("name").getType().getSize()];
        System.arraycopy(personData, 0, allocator.memoryPool, personAddress, personData.length);

        Person person = new Person();
        person.setName("John");

        // Assuming serialization/deserialization for demonstration purposes
        System.out.println("Person Name: " + person.getName());
    }
}