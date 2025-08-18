import java.util.Arrays;

public class MemoryAllocator {
    private byte[] memory;
    private int nextFreeByte;

    public MemoryAllocator(int size) {
        this.memory = new byte[size];
        this.nextFreeByte = 0;
    }

    public int allocate(int size) {
        if (nextFreeByte + size > memory.length) {
            throw new OutOfMemoryError("Not enough memory available");
        }
        int address = nextFreeByte;
        nextFreeByte += size;
        return address;
    }

    public void free(int address, int size) {
        Arrays.fill(memory, address, address + size, (byte) 0);
    }

    public static class Person {
        private String name;
        private int age;

        public Person(String name, int age) {
            this.name = name;
            this.age = age;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);

        // Allocate memory for a Person object
        int personAddress = allocator.allocate(16); // Assuming 16 bytes are enough for the Person object

        // Create a new Person object and store it in the allocated memory
        Person newPerson = new Person("John Doe", 30);

        // Simulate storing the person object at the allocated address
        // Note: In real low-level programming, you would serialize the object to bytes and store them.
        // Here we are just simulating allocation.

        System.out.println("Person allocated at address: " + personAddress);
    }
}