import java.util.Arrays;

public class MemoryAllocator {

    private static final int MEMORY_SIZE = 1024;
    private byte[] memoryBlock = new byte[MEMORY_SIZE];
    private boolean[] allocatedBlocks = new boolean[MEMORY_SIZE];

    public int allocate(int size) {
        for (int i = 0; i <= MEMORY_SIZE - size; i++) {
            if (isFree(i, size)) {
                markAsAllocated(i, size);
                return i;
            }
        }
        throw new OutOfMemoryError("Unable to allocate " + size + " bytes");
    }

    private boolean isFree(int start, int size) {
        for (int i = start; i < start + size; i++) {
            if (allocatedBlocks[i]) {
                return false;
            }
        }
        return true;
    }

    private void markAsAllocated(int start, int size) {
        for (int i = start; i < start + size; i++) {
            allocatedBlocks[i] = true;
        }
    }

    public static class Person {
        public int status;
        public String name;

        public Person(int startAddress, MemoryAllocator allocator) {
            this.status = 0;
            this.name = "John";

            // Simulating memory allocation
            byte[] personBytes = serializePerson(this);
            System.arraycopy(personBytes, 0, allocator.memoryBlock, startAddress, personBytes.length);
        }

        private byte[] serializePerson(Person person) {
            return String.format("%d,%s", person.status, person.name).getBytes();
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator();

        int sizeOfPerson = 20; // Estimated size for status and name
        int startAddress = allocator.allocate(sizeOfPerson);

        Person john = new Person(startAddress, allocator);
        
        System.out.println("Memory allocated at address: " + startAddress);
        System.out.println("Person's Name: " + Arrays.copyOfRange(allocator.memoryBlock, startAddress, startAddress + 4).clone());
        System.out.println("Person's Status: " + (int) allocator.memoryBlock[startAddress]);
    }
}