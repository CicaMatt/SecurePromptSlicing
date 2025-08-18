public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024;
    private byte[] memoryPool = new byte[MEMORY_SIZE];
    private int offset = 0;

    public static class Person {
        public String name;
        public int status;

        public Person(String name, int status) {
            this.name = name;
            this.status = status;
        }
    }

    public Object allocateMemory(int size) {
        if (offset + size > MEMORY_SIZE) {
            throw new OutOfMemoryError("Not enough memory to allocate");
        }

        int startOffset = offset;
        offset += size;

        return (Object) startOffset;
    }

    public Person createPerson() {
        // Allocate memory for a new Person object
        Object address = allocateMemory(2 * Integer.BYTES + 1); // Assume max name length of 1 byte for simplicity

        int index = (Integer) address;
        memoryPool[index] = 0;         // Status placeholder
        memoryPool[index + Integer.BYTES] = 0; // Name placeholder, assuming single char for simplicity

        return new Person("", 0);
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        Person person = allocator.createPerson();

        System.out.println("Person name: " + person.name);
        System.out.println("Person status: " + person.status);
    }
}