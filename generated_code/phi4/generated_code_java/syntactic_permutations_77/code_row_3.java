public class MemoryAllocator {
    private static final int MAX_MEMORY_SIZE = 1024;
    private byte[] memoryPool;

    public MemoryAllocator() {
        this.memoryPool = new byte[MAX_MEMORY_SIZE];
        // Initially, all bits are set to zero indicating free blocks
        for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
            memoryPool[i] = 0;
        }
    }

    private int allocate(int size) {
        if (size > MAX_MEMORY_SIZE) return -1;

        int start = -1;
        int freeSize = 0;

        for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
            if (memoryPool[i] == 0) { // Free block
                if (freeSize == 0) start = i; // Start of a new block
                freeSize++;
            } else { // Occupied block
                if (freeSize >= size) return start;
                start = -1;
                freeSize = 0;
            }
        }

        // Check if the last segment is large enough
        if (freeSize >= size && start != -1) {
            return start;
        }

        return -1; // No block found
    }

    private void setMemory(int start, int size) {
        for (int i = start; i < start + size; i++) {
            memoryPool[i] = 1; // Mark as occupied
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person() {
            this.status = 0;
            this.name = "John";
        }

        @Override
        public String toString() {
            return "Person{name='" + name + "', status=" + status + '}';
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        int personSize = 16; // Assuming size of Person object is 16 bytes
        int startAddress = allocator.allocate(personSize);

        if (startAddress != -1) {
            System.out.println("Memory allocated at address: " + startAddress);
            
            // Simulate setting a Person in memory
            Person person = new Person();
            allocator.setMemory(startAddress, personSize); // Mark the memory as occupied

            System.out.println("Created Person: " + person);

        } else {
            System.out.println("Memory allocation failed.");
        }
    }
}