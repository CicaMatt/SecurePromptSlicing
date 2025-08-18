public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Example memory size
    private byte[] memory;
    private boolean[] allocated;

    public MemoryAllocator() {
        memory = new byte[MEMORY_SIZE];
        allocated = new boolean[MEMORY_SIZE];
    }

    public int allocate(int size) {
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
                return i;
            }
        }
        throw new RuntimeException("Out of memory");
    }

    public void deallocate(int start, int size) {
        if (start >= 0 && start + size <= MEMORY_SIZE) {
            for (int i = start; i < start + size; i++) {
                allocated[i] = false;
            }
        } else {
            throw new IndexOutOfBoundsException("Invalid memory deallocation");
        }
    }

    public static class Person {
        private int status;
        private String name;

        public Person() {
            this.status = 0;
            this.name = "John";
        }

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

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        // Allocate memory for a Person object (assuming 64 bytes per object)
        int personSize = 64; 
        int pointer = allocator.allocate(personSize);

        // Create and initialize a new Person
        Person person = new Person();

        System.out.println("Person Name: " + person.getName());
        System.out.println("Person Status: " + person.getStatus());

        // Deallocate the memory for the Person object
        allocator.deallocate(pointer, personSize);
    }
}