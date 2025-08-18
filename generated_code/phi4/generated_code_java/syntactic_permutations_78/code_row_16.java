public class MemoryAllocator {
    private static final int MEMORY_SIZE = 1024; // Define the maximum memory size
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator() {
        memory = new byte[MEMORY_SIZE];
        allocated = new boolean[MEMORY_SIZE];
        for (int i = 0; i < MEMORY_SIZE; i++) {
            allocated[i] = false;
        }
    }

    public int allocate(int size) {
        if (size <= 0 || size > MEMORY_SIZE) {
            return -1; // Invalid size
        }

        int start = findFreeBlock(size);
        if (start == -1) {
            return -1; // Not enough memory
        }

        for (int i = start; i < start + size; i++) {
            allocated[i] = true;
        }
        return start;
    }

    private int findFreeBlock(int size) {
        int freeCount = 0;

        for (int i = 0; i < MEMORY_SIZE; i++) {
            if (!allocated[i]) {
                freeCount++;
                if (freeCount == size) {
                    return i - size + 1;
                }
            } else {
                freeCount = 0;
            }
        }

        return -1; // Not enough contiguous memory
    }

    public void deallocate(int start, int size) {
        if (start < 0 || start >= MEMORY_SIZE || size <= 0 || start + size > MEMORY_SIZE) {
            return; // Invalid parameters
        }

        for (int i = start; i < start + size; i++) {
            allocated[i] = false;
        }
    }

    public class Person {
        private String name;
        private int status;

        public Person(String name, int startAddress) {
            this.name = name;
            this.status = 0; // Initial status
            System.arraycopy(name.getBytes(), 0, memory, startAddress, Math.min(name.length(), MEMORY_SIZE - startAddress));
        }

        @Override
        public String toString() {
            return "Person{name='" + name + "', status=" + status + "}";
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        int address = allocator.allocate(50); // Allocate 50 bytes for a Person
        if (address != -1) {
            Person person = allocator.new Person("John Doe", address);
            System.out.println(person);
            
            allocator.deallocate(address, 50); // Deallocate memory after use
        } else {
            System.out.println("Memory allocation failed");
        }
    }
}