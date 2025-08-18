import java.util.Arrays;

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024; // Example memory pool size
    private byte[] memoryPool;
    private boolean[] usedMemory;
    
    public MemoryAllocator() {
        memoryPool = new byte[MEMORY_SIZE];
        usedMemory = new boolean[MEMORY_SIZE];
        Arrays.fill(usedMemory, false);
    }

    public int allocate(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            boolean canAllocate = true;
            for (int j = 0; j < size; j++) {
                if (usedMemory[i + j]) {
                    canAllocate = false;
                    break;
                }
            }
            
            if (canAllocate) {
                for (int j = 0; j < size; j++) {
                    usedMemory[i + j] = true;
                }
                return i;
            }
        }

        throw new OutOfMemoryError("Not enough memory to allocate " + size + " bytes.");
    }

    public void deallocate(int address, int size) {
        for (int i = 0; i < size; i++) {
            usedMemory[address + i] = false;
        }
    }

    public static class Person {
        private int status;

        public Person() {
            this.status = 0;
        }

        public int getStatus() {
            return status;
        }

        public void setStatus(int status) {
            this.status = status;
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();
        
        try {
            // Example usage: Allocate memory for a Person object
            int address = allocator.allocate(Person.class.getDeclaredField("status").getModifiers() / 8);
            System.out.println("Allocated at address: " + address);

            // Simulate creation of a new person in the allocated memory
            Person person = new Person();
            System.out.println("Person status: " + person.getStatus());

            // Deallocate memory when done
            allocator.deallocate(address, Person.class.getDeclaredField("status").getModifiers() / 8);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}