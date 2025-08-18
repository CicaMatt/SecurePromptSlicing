import java.util.HashMap;
import java.util.Map;

class MemoryAllocator {
    private static final int MEMORY_SIZE = 1024; // Arbitrary size for example
    private byte[] memoryBlock;
    private Map<Integer, String> allocations;

    public MemoryAllocator() {
        this.memoryBlock = new byte[MEMORY_SIZE];
        this.allocations = new HashMap<>();
    }

    public int allocate(int size) {
        if (size > MEMORY_SIZE || size <= 0) {
            throw new IllegalArgumentException("Invalid allocation size");
        }
        
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean free = true;
            for (int j = i; j < i + size; j++) {
                if (allocations.containsKey(j)) {
                    free = false;
                    break;
                }
            }
            
            if (free) {
                for (int j = i; j < i + size; j++) {
                    allocations.put(j, "allocated");
                }
                return i;
            }
        }
        
        throw new OutOfMemoryError("No sufficient memory available");
    }

    public void deallocate(int address) {
        if (!allocations.containsKey(address)) {
            throw new IllegalArgumentException("Invalid deallocation address");
        }
        
        for (Map.Entry<Integer, String> entry : allocations.entrySet()) {
            if (entry.getValue().equals("allocated") && entry.getKey() >= address &&
                entry.getKey() < address + MEMORY_SIZE) {
                entry.setValue(null);
            }
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person(int status, String name) {
            this.status = status;
            this.name = name;
        }

        @Override
        public String toString() {
            return "Person{" +
                    "status=" + status +
                    ", name='" + name + '\'' +
                    '}';
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        int address = allocator.allocate(1); // Allocate memory for a Person object
        System.out.println("Allocated at: " + address);

        try {
            Person person = new Person(0, "John");
            System.out.println(person);
            
            allocator.deallocate(address);
            System.out.println("Deallocated from: " + address);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}