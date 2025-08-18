public class MemoryAllocator {
    
    private byte[] memory;
    private int currentPosition;

    public MemoryAllocator(int totalSize) {
        this.memory = new byte[totalSize];
        this.currentPosition = 0;
    }

    public int allocateMemory(int size) {
        if (currentPosition + size > memory.length) {
            throw new RuntimeException("Not enough memory to allocate.");
        }
        int start = currentPosition;
        currentPosition += size;
        return start; // Return the starting position of allocated block
    }

    public void writeData(int position, byte[] data) {
        System.arraycopy(data, 0, memory, position, data.length);
    }

    public Person createPerson() {
        final int SIZE_OF_PERSON = 2 + 4 + 50; // Status (1 byte), Name Length (4 bytes), Name (50 bytes max)
        int position = allocateMemory(SIZE_OF_PERSON);

        // Write status
        writeData(position, new byte[]{0});

        // Write name length
        position += 1;
        writeData(position, Integer.toUnsignedByte(0).toString().getBytes());

        // Write name "John"
        position += 4;
        String name = "John";
        for (int i = 0; i < name.length(); i++) {
            memory[position + i] = (byte) name.charAt(i);
        }
        
        return new Person(position, SIZE_OF_PERSON);
    }

    public static class Person {
        private int position;
        private int size;

        public Person(int position, int size) {
            this.position = position;
            this.size = size;
        }

        public void printDetails() {
            System.out.println("Person details:");
            // This is a simple demonstration of accessing memory
            System.out.print("Name: ");
            for (int i = 1 + 4; i < 1 + 4 + "John".length(); i++) {
                if (memory[position + i] != 0) {
                    System.out.print((char) memory[position + i]);
                }
            }
            System.out.println("\nStatus: 0");
        }

        // Additional methods to access and manipulate person data can be added here
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(1024);
        Person person = allocator.createPerson();
        person.printDetails();
    }
}