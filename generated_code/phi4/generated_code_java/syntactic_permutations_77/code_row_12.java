public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Arbitrary size for demonstration
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator() {
        memory = new byte[MEMORY_SIZE];
        allocated = new boolean[MEMORY_SIZE];
    }

    public int allocate(int size) {
        if (size <= 0 || size > MEMORY_SIZE) {
            return -1; // Invalid size
        }
        
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = 0; j < size; j++) {
                if (allocated[i + j]) {
                    canAllocate = false;
                    break;
                }
            }
            
            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    allocated[i + j] = true;
                }
                return i; // Return the starting index
            }
        }
        
        return -1; // Not enough memory
    }

    public void deallocate(int start, int size) {
        if (start >= 0 && start < MEMORY_SIZE && size > 0 && start + size <= MEMORY_SIZE) {
            for (int i = start; i < start + size; i++) {
                allocated[i] = false;
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

        // Getters and setters
        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }

    public static Person createPerson() {
        MemoryAllocator allocator = new MemoryAllocator();
        int sizeOfPerson = Integer.BYTES + (64 * 2); // Assuming status is an int and name is a String (64 bytes for reference)
        int startIndex = allocator.allocate(sizeOfPerson);
        
        if (startIndex == -1) {
            throw new RuntimeException("Memory allocation failed");
        }
        
        Person person = new Person(0, "John");
        allocator.deallocate(startIndex, sizeOfPerson); // Free the allocated memory after use
        return person;
    }

    public static void main(String[] args) {
        Person person = createPerson();
        System.out.println("Status: " + person.getStatus());
        System.out.println("Name: " + person.getName());
    }
}