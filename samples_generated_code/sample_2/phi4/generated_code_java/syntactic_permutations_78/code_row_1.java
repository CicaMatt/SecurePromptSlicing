public class MemoryManager {

    private byte[] memory;
    private int freePointer;

    public MemoryManager(int size) {
        memory = new byte[size];
        freePointer = 0;
    }

    public int allocate(int size) {
        if (freePointer + size > memory.length) {
            return -1; // Not enough memory
        }
        int address = freePointer;
        freePointer += size;
        return address;
    }

    public void deallocate(int address, int size) {
        // Simple deallocation logic for demonstration purposes.
        // In a real scenario, this would involve more complex management.
        if (address + size <= memory.length && address >= 0) {
            System.arraycopy(memory, freePointer, memory, address, size);
            freePointer = address;
        }
    }

    public static class Person {
        private int status;

        public Person() {
            this.status = 0; // Set the status to 0
        }

        public void setStatus(int status) {
            this.status = status;
        }

        public int getStatus() {
            return this.status;
        }
    }

    public static void main(String[] args) {
        MemoryManager manager = new MemoryManager(1024);

        // Allocate memory for a Person object (assuming size of 16 bytes)
        int personAddress = manager.allocate(Person.class.getDeclaredFields().length * Integer.BYTES);
        if (personAddress != -1) {
            Person person = new Person();
            System.out.println("Person status: " + person.getStatus());
        } else {
            System.out.println("Failed to allocate memory for a Person.");
        }
    }
}